def main():
    height = -1
    # get the height within the interval
    while height < 1 or height > 8:
        val = input("Height: ")
        # only digits allowed
        if val.isdigit():
            height = int(val)

    # Print the pyramids
    for level in reversed(range(height)):
        # For readibility these variables were created. Although they can be placed directly inside the print statement.
        l_spaces = (height - (height - level))*' '
        l_hashes = (height - level)*'#'
        r_hashes = (height - level)*'#'
        print(l_spaces + l_hashes + "  " + r_hashes)


if __name__ == "__main__":
    main()