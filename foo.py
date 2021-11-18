def simplify(base, sequence):
    numerator = 1
    denominator = sequence[-1]
    print(sequence[-2::-1])
    for d in sequence[-2::-1]:
        temp = denominator
        denominator = d * denominator + numerator
        numerator = temp
        print(numerator, denominator)

b = 3
seq = [3, 7, 15, 1, 292, 1, 1, 1, 2, 1, 3]
simplify(b, seq)
