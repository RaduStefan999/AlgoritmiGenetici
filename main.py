import numpy as np
import sys
import math


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
        result = x*x - 10*math.cos(2*math.pi*x)
    return 10 * analyser_obj.dimensions + result


def simulated_annealing():
    return


if __name__ == '__main__':
    analyser = FunctionAnalyser(-5.12, 5.12, 5, 2, rastrigin)

    if len(sys.argv) > 1:
        if sys.argv[1] == "hill_climbing":
            print(round(analyser.hill_climbing(10, "best_improvement"), 5))
        elif sys.argv[1] == "simulated_annealing":
            analyser.simulated_annealing()



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