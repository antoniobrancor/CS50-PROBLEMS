def main():
    height = get_height()
    for i in range(height):
        print((" " * (height - i - 1)) + ("#" * (i + 1)) + (" "*2) + ("#" * (i + 1)))


def get_height():
    while True:
        try:
            n = int(input("Height: "))
            if n > 0 and n < 9:
                break
        except ValueError:
            print("Imput has to be integer not greater than 8!")
    return n


main()
