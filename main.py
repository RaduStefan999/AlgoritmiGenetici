import numpy as np
import sys
import math
import random
import time


class FunctionAnalyser:
    def __init__(self, a, b, precision, dimensions, eval_function):
        self.a = a
        self.b = b
        self.precision = precision
        self.dimensions = dimensions
        self.eval = eval_function

        number_size = (b - a) * pow(10, precision)
        data_size = int(math.floor(math.log(number_size, 2)) + 1)

        self.data_size = data_size

    def to_number(self, bit_str):
        base_power = 1
        number = 0

        for bit in bit_str:
            number = number + base_power * int(bit)
            base_power = base_power * 2

        number = self.a + number * (self.b - self.a) / (pow(2, self.data_size))
        return number

    def first_improve(self, solution):
        duplicate = np.copy(solution)

        for argument in solution:
            index = 0
            for bit in argument:
                argument[index] = not argument[index]

                if self.eval(self, solution) < self.eval(self, duplicate):
                    return

                argument[index] = not argument[index]

                index = index + 1

    def best_improve(self, solution):
        best = np.copy(solution)

        for argument in solution:
            index = 0
            for bit in argument:
                argument[index] = not argument[index]

                if self.eval(self, solution) < self.eval(self, best):
                    best = np.copy(solution)

                argument[index] = not argument[index]

                index = index + 1

        solution[:] = best

    def hill_climbing(self, iterations, improvement):
        best_solution = np.random.choice(a=[False, True], size=(self.dimensions, self.data_size))

        for i in range(1, iterations + 1):
            local = False
            local_solution = np.random.choice(a=[False, True], size=(self.dimensions, self.data_size))
            improved_solution = np.copy(local_solution)

            while not local:
                if improvement == "first_improvement":
                    self.first_improve(improved_solution)
                elif improvement == "best_improvement":
                    self.best_improve(improved_solution)

                if self.eval(self, improved_solution) < self.eval(self, local_solution):
                    local_solution = np.copy(improved_solution)
                else:
                    local = True

            if self.eval(self, local_solution) < self.eval(self, best_solution):
                best_solution = np.copy(local_solution)

            print(i)

        return self.eval(self, best_solution)

    def random_neighbourhood(self, solution):
        argument_index = random.randint(0, self.dimensions - 1)
        bit_index = random.randint(0, self.data_size - 1)
        solution[argument_index, bit_index] = not solution[argument_index, bit_index]

    def simulated_annealing(self, iterations):
        temperature = 2000

        candidate_solution = np.random.choice(a=[False, True], size=(self.dimensions, self.data_size))

        for i in range(1, iterations + 1):
            for j in range(1, self.data_size * 3):
                random_neighbour_solution = np.copy(candidate_solution)
                self.random_neighbourhood(random_neighbour_solution)

                evalc = self.eval(self, candidate_solution)
                evaln = self.eval(self, random_neighbour_solution)

                if evaln < evalc:
                    candidate_solution = np.copy(random_neighbour_solution)
                elif random.uniform(0, 1) < math.exp(-abs((evaln - evalc) / temperature)):
                    candidate_solution = np.copy(random_neighbour_solution)

            temperature = temperature * 0.9

            print(i)

        return self.eval(self, candidate_solution)


def de_jong(analyser_obj, solution):
    result = 0
    for argument in solution:
        x = analyser_obj.to_number(argument)
        result = result + x*x
    return result


def schwefel(analyser_obj, solution):
    result = 0
    for argument in solution:
        x = analyser_obj.to_number(argument)
        result = result + (-x)*math.sin(math.sqrt(abs(x)))
    return result


def rastrigin(analyser_obj, solution):
    result = 0
    for argument in solution:
        x = analyser_obj.to_number(argument)
        result = result + x*x - 10*math.cos(2*math.pi*x)
    return 10 * analyser_obj.dimensions + result


def michalewicz(analyser_obj, solution):
    result = 0
    i = 1
    for argument in solution:
        x = analyser_obj.to_number(argument)
        result = result + math.sin(x) * pow((math.sin(i * x*x / math.pi)), 2*10)
        i = i + 1
    return -result


if __name__ == '__main__':
    begin = time.time()

    analyser = FunctionAnalyser(-5.12, 5.12, 5, 5, rastrigin)

    if len(sys.argv) > 1:
        if sys.argv[1] == "hill_climbing":
            print(analyser.hill_climbing(1000, "best_improvement"))
        elif sys.argv[1] == "simulated_annealing":
            print(analyser.simulated_annealing(1000))

    end = time.time()

    print(f"Timpul total pentru rularea programului este {end - begin}")



# t := 0
# initialize best
# repeat
#     local := FALSE
#     select a candidate solution (bitstring) vc at random
#     evaluate vc
#     repeat
#         vn := Improve(Neghborhood(vc))
#         if eval(vn) is better than eval(vc)
#         then vc := vn
#         else local := TRUE
#     until local
#     t := t + 1
#     if vc is better than best
#     then best := vc
# 1 1 1 0 0 1 - + 1
# 0 1 1 0 0 0 - + 1 + 32
# until t = MAX

#t := 0
#initialize the temperature T
#select a current candidate solution (bitstring) vc at random
#evaluate vc
#repeat
#    repeat
#        select at random vn: a neighbor of vc
#        if eval(vn) is better than eval(vc)
#            then vc := vn
#            else if random[0,1) < exp(-|eval(vn) - eval(vc)| / T)
#                then vc := vn
#    until (termination-condition)
#    T := g(T; t)
#    t := t + 1
#until (halting-criterion)