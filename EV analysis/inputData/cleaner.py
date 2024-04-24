with open("./229 NO RECT 1.txt", "r") as f:
    data = f.readlines()


with open("./data_test_cleaned.txt", "w") as f:
    for line in data:
        f.write(line.replace(",\n", "\n"))
