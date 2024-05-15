from cs50 import get_float


def main():
    while True:
        change = get_float("Change: ")
        if change >= 0:
            calculation(change)
            break


def calculation(change):
    counts = 0
    change = change * 100

    #  quarters (25¢)
    if change >= 25:
        counts = counts + change // 25
        change = change % 25
        # print("counts 25: ","{:.0f}".format(counts))
        # print("change 10: ",change)

    # dimes (10¢)
    if change >= 10:
        counts = counts + change // 10
        change = change % 10
        # print("counts 10: ","{:.0f}".format(counts))
        # print("change 10: ",change)

    # nickels (5¢)
    if change >= 5:
        counts = counts + change // 5
        change = change % 5
        # print("counts 5: ","{:.0f}".format(counts))
        # print("change 5: ",change)

    # pennies (1¢)
    if change >= 1:
        counts = counts + change // 1
        change = change % 1
        # print("counts 1: ","{:.0f}".format(counts))
        # print("change 1: ",change)

    # print("{:.0f}".format(counts))
    counts = int(counts)
    print(counts)


main()
