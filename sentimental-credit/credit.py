cardNumber = input("Card number:")
intCardNumber = int(cardNumber)
sum = 0
mult = 0
rawValue = 0


for i in range(len(cardNumber)):
    print(f"{intCardNumber}")
    # Sum digits
    is_sum = i % 2 == 0
    if (is_sum):
        sum = sum + (intCardNumber % 10)
    # Multiply then sum digts
    else:
        multResult = 2 * (intCardNumber % 10)
        if multResult > 9:
            mult = multResult - 9
        else:
            mult = multResult

    rawValue = (mult + sum) + rawValue
    mult = 0
    sum = 0

    if intCardNumber < 100 and intCardNumber > 9:
        firstTwoDigits = intCardNumber

    intCardNumber = intCardNumber // 10


cardValue = ((rawValue) % 10)

if cardValue != 0:
    print(f"INVALID")
elif (len(cardNumber) > 12 and len(cardNumber) < 17 ) and (firstTwoDigits // 10 == 4):
    print("VISA")
elif (len(cardNumber) == 15 and (firstTwoDigits == 34 or firstTwoDigits ==37)):
    print("AMEX")
elif (len(cardNumber) == 16 and (firstTwoDigits > 50 and firstTwoDigits < 56)):
    print("MASTERCARD")
else:
    print("INVALID")
