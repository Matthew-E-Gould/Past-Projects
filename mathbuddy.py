import time
import math
import random


class MathBuddy:
    def __init__(self):
        self.operations0 = ["(", ")"]
        self.operations1 = ["^"]
        self.operations2 = ["/", "*"]
        self.operations3 = ["+", "-"]
        self.num_ref = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]
        self.opr_ref = self.operations3  # + self.operations2 #+ self.operations1 #+ self.operations0

        self.__equ_array = []
        self.__equ_array_len = 0
        self.__equ_string = ""

        random.seed(time.time())
        print("Hello World. :)")

    def rec_fib(self, x):
        if x < 3:
            return 1
        else:
            return self.rec_fib(x - 1) + self.rec_fib(x - 2)

    def for_fib(self, x):
        top = 1
        bot = 0
        for i in range(x - 1):
            temp = top
            top = bot + top
            bot = temp
        return top

    def rec_factorial(self, x):
        temp = x
        if x > 0:
            temp *= self.rec_factorial(x - 1)
            return temp
        else:
            return 1

    def factorial(self, x):
        value = 1
        for x in range(1, x + 1):
            value *= x
        return value

    def __equ_read(self):
        size = len(self.__equ_string)
        temp_val = 0
        self.__equ_array.clear()
        for x in range(size):
            if self.__equ_string[x] in self.num_ref:
                temp_val = temp_val * 10 + int(self.__equ_string[x])

            elif self.__equ_string[x] in self.opr_ref:
                if self.__equ_string[x] in self.operations0:
                    if temp_val > 0:
                        self.__equ_array.append(temp_val)

                    self.__equ_array.append(self.__equ_string[x])
                else:
                    self.__equ_array.append(temp_val)
                    temp_val = 0
                    self.__equ_array.append(self.__equ_string[x])

            else:
                print("This functionality doesn't handle anything other than:")
                print(self.num_ref)
                print(self.opr_ref)
                print(":(")
                return False

        if temp_val > 0:
            self.__equ_array.append(temp_val)

        return True

    def __equ_b(self):
        # self.__equ_array
        self.__equ_array_len = len(self.__equ_array)
        location_array = []
        if self.operations0[0] in self.__equ_string:
            for x in range(self.__equ_array_len):
                if self.operations0[0] in self.__equ_array[x]:
                    start = x
                    end = -1
                    depth = 0
                    found = False
                    for y in range(self.__equ_array_len - x):
                        if self.__equ_array[y+x] == self.operations0[0] and not found:
                            depth = depth + 1
                        elif self.__equ_array[y+x] == self.operations0[1] and not found:
                            depth = depth - 1
                            if depth <= 0:
                                end = y+x
                                found = True

                    location_array.append([start, end])

                elif self.operations0[1] in self.__equ_array[x]:
                    found = False
                    for y in range(len(location_array)):
                        temp_array = location_array[y]
                        if x == temp_array[1]:
                            found = True

                    if not found:
                        location_array.append([-1, x])

        else:
            print("No '(' brackets found :P")
            return False

        print(str(self.__equ_array)+"      [S:"+str(self.__equ_array_len)+"]")
        print("Locations Detected: "+str(location_array))
        return True

    def __equ_b2(self):
        return True

    def __equ_o(self):
        return True

    def __equ_o2(self):
        return True

    def __equ_dm(self):
        return True

    def __equ_dm2(self):
        return True

    def __equ_as(self):
        return True

    def __equ_as2(self):
        return True

    def __equ_bodmas(self):
        val1 = 0
        val2 = 0
        oper = ""
        if self.__equ_b():
            self.__equ_b2()
        if self.__equ_o():
            self.__equ_o2()
        if self.__equ_dm():
            self.__equ_dm2()
        if self.__equ_as():
            self.__equ_as2()

    def brackets_search(self, string):
        string = str(string)
        string_len = len(string)
        location_array = []
        if self.operations0[0] in string:
            for x in range(string_len):
                if self.operations0[0] in string[x]:
                    start = x
                    end = -1
                    depth = 0
                    found = False
                    for y in range(string_len - x):
                        if string[y+x] == self.operations0[0] and not found:
                            depth = depth + 1
                        elif string[y+x] == self.operations0[1] and not found:
                            depth = depth - 1
                            if depth <= 0:
                                end = y+x
                                found = True

                    location_array.append([start, end])

                elif self.operations0[1] in string[x]:
                    found = False
                    for y in range(len(location_array)):
                        temp_array = location_array[y]
                        if x == temp_array[1]:
                            found = True

                    if not found:
                        location_array.append([-1, x])

        else:
            print("no '(' in string :|")
            return

        print(string+"      [S:"+str(string_len)+"]")
        print("Locations Detected: "+str(location_array))

    def calculate(self, input_equation_str):
        self.__equ_string = str(input_equation_str)

        print("Reading Equation: "+self.__equ_string+" 0-0")
        self.__equ_read()
        print("Equation read as: "+str(self.__equ_array)+" :o")

        self.__equ_bodmas()


def main():
    bot = MathBuddy()
    print("")

    bot.brackets_search("(t)e(st)((ing)) ))) ((((((( (())")
    print("")

    bot.calculate("INVALID INPUT")
    print("")
    bot.calculate("12+34")
    print("")
    bot.calculate("++++12+34++++")
    print("")
    bot.calculate("12+34*56")
    print("")
    bot.calculate("12+34*56")
    print("")

    print("")

    print("")
    val = 980  # don't put this value much higher than this - my IDE acts weird
    start = time.time()
    print(str(val)+"! = "+str(bot.factorial(val)))
    end = time.time()
    print("for loop:  "+str(end-start)+" seconds")

    print("")
    start = time.time()
    print(str(val)+"! = "+str(bot.rec_factorial(val)))
    end = time.time()
    print("recursive: "+str(end-start)+" seconds")

    print("")
    val = 40
    print("102334155 (fibonacci: 40)")

    print("")
    start = time.time()
    print(str(bot.for_fib(val)))
    end = time.time()
    print("for loop:  "+str(end-start)+" seconds")

    print("")
    start = time.time()
    print(str(bot.rec_fib(val)))
    end = time.time()
    print("recursive: "+str(end-start)+" seconds")


if __name__ == "__main__":
    main()

