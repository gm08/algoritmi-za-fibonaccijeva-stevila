# Algoritmi za Fibonaccijeva števila
Zbirka algoritmov za generiranje velikih fibonaccijevih števil v Javi in C-ju
### Seznam algoritmov:
- **fibonacci1.java / fibonacci1.c**<br/>
  navadni rekurzivni algoritem
- **fibonacci2.java / fibonacci2.c**<br/>
  rekurzivni algoritem z memoizacijo z navadno tabelo
- **fibonacci3.java / fibonacci3.c**<br/>
  rekurzivni algoritem z memoizacijo s hash tabelo<br/>
  - *fibonacci31.c* - za realizacijo hash tabele se uporablja header file [uthash.h](https://troydhanson.github.io/uthash/)
  - *fibonacci32.c* - lastna implementacija hash tabele
- **fibonacci4.java / fibonacci4.c**<br/>
  iterativni algoritem
- **fibonacci5.java / fibonacci5.c**<br/>
  matrični algoritem z iterativnim potenciranjem matrike [[1, 1], [1, 0]]
- **fibonacci6.java / fibonacci6.c**<br/>
  optimiziran matrični algoritem  z rekurzivnim množenjem polovičnih potenc matrike [[1, 1], [1, 0]]
- **fibonacci7.java / fibonacci7.c**<br/>
  algoritem na podlagi rekurzivne formule:<br/>
    - če je n sod:<br/>
      k = n / 2<br/>
      f(n) = (2 * f(k-1) + f(k)) * f(k)
    - če je n lih:<br/>
      k = (n+1) / 2<br/>
      f(n) = f(k) * f(k) + f(k-1) * f(k-1)
- **fibonacci8.java / fibonacci8.c**<br/>
  algoritem na podlagi Binetove formule
