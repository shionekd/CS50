from cs50 import get_int


def main():
    while True:
        height = get_int("Height: ")
        if 0 < height < 9:
            for i in range(height):
                print_hash(height - i - 1, i + 1)
            break


def print_hash(spaces, bricks):
    for s in range(spaces):
        print(" ", end="")

    for b in range(bricks):
        print("#", end="")
    print("")


main()
