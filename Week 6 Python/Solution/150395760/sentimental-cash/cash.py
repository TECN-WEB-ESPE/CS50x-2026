from cs50 import get_float

while True:
    try:
        dollars = get_float("Change owed: ")
        # Validar que sea un numero no negativo
        if dollars >= 0:
            break
    except ValueError:
        continue

#Convertir a centavos y redondear para evitar errores de precisión
cents = round(dollars * 100)
count = 0

# 1. Quarters (25c)
while cents >= 25:
    cents = cents - 25
    count += 1

# 2. Dimes (10c)
while cents >= 10:
    cents = cents - 10
    count += 1

# 3. Nickels (5c)
while cents >= 5:
    cents = cents - 5
    count += 1

# 4. Pennies (1c)
while cents >= 1:
    cents = cents - 1
    count += 1

print(count)
