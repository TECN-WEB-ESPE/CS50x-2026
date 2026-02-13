from cs50 import get_int #importar la funcion para usar enteros

while True:
    n = get_int("Height: ")
    # Si n está entre 1 y 8, sino romper el bloque
    if n > 0 and n < 9:
        break

for i in range(1, n + 1):
    # Imprime (espacios) + (hashtags)
    print(" " * (n - i) + "#" * i)
