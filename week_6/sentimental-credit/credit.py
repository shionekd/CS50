from cs50 import get_string


def main():
    while True:
        number = get_string("Number: ")
        if (number.isdecimal()):
            if (len(number) == 13) or (len(number) == 15) or (len(number) == 16):
                sums = luhn_Algorithm(number)
                if sums % 10 == 0:
                    check_comp(number)
                else:
                    print("INVALID")
            else:
                print("INVALID")
            break


def luhn_Algorithm(number):
    sums = 0
    number = number[::-1]
    for n in range(1, len(number), 2):
        num1, num2 = (int(number[n]) * 2) // 10, (int(number[n]) * 2) % 10
        # print("number[n]: ",number[n])
        # print(f'num1: {num1}, num2: {num2}')
        sums += num1 + num2
    for n in range(0, len(number), 2):
        sums += int(number[n])

    return sums


def check_comp(number):
    if (len(number) == 15) and (int(number[0]) == 3):
        if (int(number[1]) == 4) or (int(number[1]) == 7):
            print("AMEX")
        else:
            print("INVALID")

    elif (len(number) == 16):
        if (int(number[0]) == 5):
            if (int(number[1]) == 1) or (int(number[1]) == 2) or (int(number[1]) == 3) or (int(number[1]) == 4) or (int(number[1]) == 5):
                print("MASTERCARD")
            else:
                print("INVALID")

        elif (int(number[0]) == 4):
            print("VISA")

        else:
            print("INVALID")

    elif (len(number) == 13) and (int(number[0]) == 4):
        print("VISA")

    else:
        print("INVALID")


main()
