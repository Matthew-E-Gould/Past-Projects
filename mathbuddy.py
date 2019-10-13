from time import time, strftime, gmtime


class MathBuddy:
    def __init__(self):
        self.__operations0 = ["(", ")"] # brackets
        self.__operations1 = ["^", "!"] # powers
        self.__operations2 = ["/", "*", "%"] # multiplication
        self.__operations3 = ["+", "-"] # addition
        self.__num_ref = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"] # numbers
        self.__not_ref = [".", ","] # notation
        self.__opr_ref = self.__operations0 + self.__operations1 + self.__operations2 + self.__operations3
        self.__opr_ref_dev = self.__operations1 + self.__operations2 + self.__operations3

        self.__equ_array = [] # stores equation
        self.__equ_string = "" # stroes string equiv of equation

        self.answer = 0 # answer
        self.ans_hist = [] # history of answers
        self.log = [] # log of last equation

        # output to say that bot has started up
        print("Hello World. :)")
        print(strftime("It is: %d/%m/%Y %H:%M:%S -> GMT", gmtime()))
        print("You are running v1.5.3 of MathBuddy :D")
        print("")

    ############################
    #  BODMAS module  ##########
    ############################
    def __equ_read(self):  # read equation, turns [1,2,+,3] to [12,+,3] etc.
        size = len(self.__equ_string)  # getting size of string
        int_vals = 0  # stores the values of integers
        self.__equ_array.clear()
        decimal_last = False
        for x in range(size):  # reading each character of the string
            if self.__equ_string[x] in self.__num_ref:  # if current character is a number
                int_vals = int_vals * 10 + int(self.__equ_string[x])  # compiling decimal string entries
                decimal_last = True

            elif self.__equ_string[x] in self.__opr_ref:  # if current character isn't a decimal
                if self.__equ_string[x] in self.__operations0:  # if current character is a bracket
                    if decimal_last:
                        self.__equ_array.append(int_vals)  # store temp int if there was one
                        int_vals = 0

                    self.__equ_array.append(self.__equ_string[x])  # store current string value

                else:  # use of else to make sure [+] is made possible as an equation: [0,+,0]
                    if decimal_last:
                        self.__equ_array.append(int_vals)  # store temp int if there was one
                        int_vals = 0
                    self.__equ_array.append(self.__equ_string[x])  # store current string value

                decimal_last = False

            else:  # fail condition
                print("I don't handle anything other than:")
                print(self.__num_ref)
                print(self.__opr_ref)
                print(":(")
                return False

        if decimal_last:
            self.__equ_array.append(int_vals)

        return True

    def __equ_b(self, equ_array):  # working out bracket locations
        # setup
        array_len = len(equ_array)
        location_array = []
        invalid_ends = []
        for x in range(array_len):
            if self.__operations0[0] == equ_array[x]:  # if current character is "("
                # setup default values for system use
                start = x
                end = -1
                depth = 0
                found = False
                for y in range(array_len - x):  # looking at the rest of the string after the "("
                    if equ_array[y + x] == self.__operations0[0] and not found:  # if "("
                        depth = depth + 1  # 1 layer deeper
                    elif equ_array[y + x] == self.__operations0[1] and not found:  # if ")"
                        depth = depth - 1  # 1 layer less
                        if depth <= 0:  # if we have found the correct ")"
                            end = y + x  # save end position
                            found = True  # need to work out how i can use break

                location_array.append([start, end])  # store locations for "(" ")" pair

            elif self.__operations0[1] == equ_array[x]:  # if current character is ")"
                found = False
                for y in range(len(location_array)):  # look through the stored array
                    if x == location_array[y][1]:  # if bracket has already been paired then its all good
                        found = True

                if not found:
                    invalid_ends.append(x)  # if never paired then record invalid ")" location

        changes = 0
        while len(invalid_ends) > 0:
            del equ_array[invalid_ends[0]-changes]
            del invalid_ends[0]
            changes += 1
            print("I noticed that there was a weird ')', so I got rid of it! ;)")
            print(equ_array)

        return len(location_array) > 0, location_array, equ_array

    def __equ_b2(self, equ_array, loc_array):  # works out how to use known, valid brackets
        # setup
        brackets = loc_array
        change = 0
        while len(brackets) > 0:  # while the bot can still do stuff
            # getting start and end location
            start = loc_array[0][0] - change
            end = loc_array[0][1] - change
            temp_equ = equ_array[start + 1:end]
            print("Working out sub equation with BODMAS: " + str(temp_equ))
            temp_answer = self.__equ_bodmas(temp_equ)  # recurse the equation in the brackets
            del equ_array[start:end + 1]
            equ_array.insert(start, temp_answer)

            torf = True
            while torf and len(loc_array) > 0:  # while there are still valid pairs to be deleted
                if loc_array[0][0]-change < end:  # if there were a set of brackets in another set of brackets
                    del loc_array[0]  # deleting all brackets that have been done
                else:  # will only trigger when outside of brackets encapsulation
                    torf = False  # end while loop

            change += end - start  # accounting for the simplification of equation
            #self.log.append(''.join(str(e) for e in equ_array)) #<<<<<<<<<<<<<<<<<<<<<<<<<

        return equ_array

    def __equ_o(self, equ_array):
        # setup
        array_len = len(equ_array)
        location_array = []
        for x in range(array_len):
            if equ_array[x] in self.__operations1:
                location_array.append(x)  # saving location of operation

        return location_array

    def __equ_o2(self, equ_array, loc_array):
        # setup
        count = 0
        x = 0
        while x < len(loc_array):  # going through the loc_array
            temp = loc_array[x] - count
            op_type = equ_array[temp]  # looking at the type of operator (!, ^, etc.)
            loc1 = temp - 1
            val1 = equ_array[loc1]  # getting value left of operator
            if op_type == self.__operations1[0]:  # ^
                loc2 = temp + 1
                backup_val2 = val2 = equ_array[loc2]  # getting value right of operator
                temp_answer = 1
                while val2 > 0:
                    temp_answer *= val1
                    val2 -= 1

                self.log.append(str(val1)+"^"+str(backup_val2)+"="+str(temp_answer))
                del equ_array[loc1:loc2+1]
                equ_array.insert(loc1, temp_answer)
                count += 2

            elif op_type == self.__operations1[1]:  # !
                temp_answer = self.factorial(val1)
                self.log.append(str(val1) + "!" + "=" + str(temp_answer))
                del equ_array[temp]
                equ_array[loc1] = temp_answer
                count += 1

            x += 1

        return equ_array

    def __equ_dm(self, equ_array):
        array_len = len(equ_array)
        location_array = []
        for x in range(array_len):
            if equ_array[x] in self.__operations2:
                location_array.append(x)

        for x in range(len(equ_array)-1):  # stuff to make 3(2)=6 work
            if isinstance(equ_array[x], int or float) and isinstance(equ_array[x+1], int or float):
                location_array.append(-1)

        return location_array

    def __equ_dm2(self, equ_array, loc_array):
        try:
            loc_array.remove(-1)
        except:
            True
        count = 0
        temp_answer = 0
        for x in range(len(loc_array)):
            temp = loc_array[x] - count
            loc1 = temp - 1
            loc2 = temp + 1
            val1 = equ_array[loc1]
            val2 = equ_array[loc2]
            if self.__operations2[0] in equ_array[temp]:  # if char is "/"
                temp_answer = val1 / val2
                self.log.append(str(val1) + "/" + str(val2) + "=" + str(temp_answer))
            elif self.__operations2[1] in equ_array[temp]:  # if char is "*":
                temp_answer = val1 * val2
                self.log.append(str(val1) + "x" + str(val2) + "=" + str(temp_answer))
            elif self.__operations2[2] in equ_array[temp]:  # if char is "*":
                temp_answer = val1 % val2
                self.log.append(str(val1) + "%" + str(val2) + "=" + str(temp_answer))

            del equ_array[loc1:loc2+1]
            equ_array.insert(loc1, temp_answer)
            count += 2

        count = 0
        x = 0
        while x < len(equ_array)-1:  # stuff to make 3(2)=6 work
            if isinstance(equ_array[x], int or float) and isinstance(equ_array[x+1], int or float):
                temp_answer = equ_array[x-count] * equ_array[x-count+1]
                self.log.append(str(equ_array[x-count]) + "x" + str(equ_array[x-count+1]) + "=" + str(temp_answer))
                del equ_array[x-count+1]
                count += 1
                equ_array[x] = temp_answer
            x += 1

        return equ_array

    def __equ_as(self, equ_array):
        array_len = len(equ_array)
        location_array = []
        for x in range(array_len):
            if equ_array[x] in self.__operations3:
                location_array.append(x)

        return location_array

    def __equ_as2(self, equ_array, loc_array):
        count = 0
        temp_answer = 0
        for x in range(len(loc_array)):
            temp = loc_array[x] - count
            loc1 = temp - 1
            loc2 = temp + 1
            val1 = equ_array[loc1]
            val2 = equ_array[loc2]
            if self.__operations3[0] in equ_array[temp]:  # if char is "+"
                temp_answer = val1 + val2
                self.log.append(str(val1) + "+" + str(val2) + "=" + str(temp_answer))
            elif self.__operations3[1] in equ_array[temp]:  # if char is "-":
                temp_answer = val1 - val2
                self.log.append(str(val1) + "-" + str(val2) + "=" + str(temp_answer))

            del equ_array[loc1:loc2+1]
            equ_array.insert(loc1, temp_answer)
            count += 2
        return equ_array

    def __equ_bodmas(self, equ_arr):
        print("-\nDetecting "+str(self.__operations0)+" for "+str(equ_arr))
        valid, locs, temp_equ_arr = self.__equ_b(equ_arr)
        if valid:
            print("Working out stuff relating to "+str(self.__operations0))
            equ_arr = self.__equ_b2(temp_equ_arr, locs)
            #self.log.append(''.join(str(e) for e in equ_arr)) #<<<<<<<<<<<<<<<<<<<<<<<<<
            print("The Equation now looks like: " + str(equ_arr))
        del valid, locs, temp_equ_arr

        print("-\nDetecting "+str(self.__operations1)+" for "+str(equ_arr))
        locs = self.__equ_o(equ_arr)
        if len(locs) > 0:
            print("Working out stuff relating to "+str(self.__operations1))
            equ_arr = self.__equ_o2(equ_arr, locs)
            #self.log.append(''.join(str(e) for e in equ_arr))#<<<<<<<<<<<<<<<<<<<<<<<<<
            print("The Equation now looks like: " + str(equ_arr))

        print("-\nDetecting " + str(self.__operations2)+" for "+str(equ_arr))
        locs = self.__equ_dm(equ_arr)
        if len(locs) > 0:
            print("Working out stuff relating to " + str(self.__operations2))
            equ_arr = self.__equ_dm2(equ_arr, locs)
            #self.log.append(''.join(str(e) for e in equ_arr)) #<<<<<<<<<<<<<<<<<<<<<<<<<
            print("The Equation now looks like: " + str(equ_arr))

        print("-\nDetecting " + str(self.__operations3)+" for "+str(equ_arr))
        locs = self.__equ_as(equ_arr)
        if len(locs) > 0:
            print("Working out stuff relating to " + str(self.__operations3))
            equ_arr = self.__equ_as2(equ_arr, locs)
            #self.log.append(''.join(str(e) for e in equ_arr)) #<<<<<<<<<<<<<<<<<<<<<<<<<

        return equ_arr[0]
#######################################

    def rec_fib(self, x):
        if x < 3:
            return 1
        else:
            return self.rec_fib(x - 1) + self.rec_fib(x - 2)

    def fibonacci(self, x):
        top = 1
        bot = 0
        for i in range(x - 1):
            temp = top
            top = bot + top
            bot = temp
        return top

    def rec_fac(self, x):
        temp = x
        if x > 0:
            temp *= self.rec_fac(x - 1)
            return temp
        else:
            return 1

    def factorial(self, x):  # for loop factorial function
        value = 1
        for x in range(1, x + 1):
            value *= x
        return value

    def calculate(self, input_equation_str):
        self.log.clear()
        self.__equ_string = str(input_equation_str)
        print("Starting the timer!")
        start_time = time()
        print("Reading Equation: "+self.__equ_string)
        self.__equ_read()
        print("Equation Read as: "+str(self.__equ_array))
        self.log.append(''.join(str(e) for e in self.__equ_array)+"=?")

        print("Now Doing the BODMAS :)")
        self.answer = self.__equ_bodmas(self.__equ_array)
        end_time = time()
        print("I've Got an Answer!")
        print("======")
        print(self.__equ_string+" = "+str(self.answer))
        self.log.append(self.__equ_string+"="+str(self.answer))
        print("I did that in "+str(end_time-start_time)+" seconds")
        print("======")
        print("")

        self.ans_hist.append(self.answer)
        return self.answer

    def out_log(self):
        x = 0
        while x < len(self.log):
            print(self.log[x])
            x += 1

    def ret_log(self):
        return self.log

    def help(self):
        print("Commands:")
        
        print("calculate(<equation>) - calculates <equation>")
        
        print("factoral(<number>) - finds out the factor of <number>")
        print("rec_fac(<number>) - finds out the factor of <number>, recursively")
        
        print("fibonacci(<number>) - finds out the fibonacci of <number>")
        print("rec_fib(<number>) - finds out the fibonacci of <number>, recursively")

        print("out_log() - outputs the log")
        print("ret_log() - returns the log")

# from mathbuddy import *
# bot = MathBuddy()
