float aX, aY, aZ, a;

aX = x * 0.00305; #svuda ide *0.00305 jer ce opseg mog senzora biti do 100*g.  LIS331HH koristi 16-bitni registar. To znači da senzor može očitavati vrednosti unutar opsega 16-bitnog broja. 
 #Posto je moj opseg do 100*g onda 100*g delim sa brojem 32,767.
aY = y * 0.00305;
aZ = z * 0.00305;

a = sqrt(aX * aX + aY * aY + aZ * aZ);

if (a > 20) {
  sendSOS();
}
