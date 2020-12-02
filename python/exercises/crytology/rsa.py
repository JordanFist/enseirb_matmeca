from exo1 import generate_prime, prime_with, inverse_modulaire

def rsa_key():
    p = generate_prime(1, 10000)
    q = generate_prime(1, 10000)
    n = p * q
    phi = n - p - q +1 
    e = prime_with(phi)
    while (e >= phi):
        e = prime_with(phi)
    d = inverse_modulaire(e, phi)
    #while (d >= phi):
        #d = inverse_modulaire(e, phi)
    return (n, e)

print(rsa_key())