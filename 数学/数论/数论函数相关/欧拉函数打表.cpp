//欧拉函数的一些性质：
//① 当m,n互质时，有phi（m*n）= phi（m）*phi（n）；
//
//② 若i%p==0，有phi（i*p） = p * phi(i)；
//
//③ 对于互质x与p，有x^phi§≡1（mod p),因此x的逆元为x^(phi§-1)，即欧拉定理。
//（特别地，当p为质数时，phi（p）=p-1,此时逆元为x^(p-2)，即费马小定理）
//
//④ 当n为奇数时，phi(2n)=phi(n)
//
//⑤ 若x与p互质，则p-x也与p互质，因此小于p且与p互质的数之和为phi(x)*x/2;
//
//⑥N>1，不大于N且和N互素的所有正整数的和是 1/2 *N *eular(N)。
//
//⑦若(N%a == 0 && (N/a)%a==0) 则有:E(N)=E(N/a)*a;
//
//⑧若(N%a==0 && (N/a)%a!=0) 则有:E(N)=E(N/a)*(a-1);
void get_phi()
{
    int i, j, k;
    k = 0;
    for(i = 2; i < maxn; i++)
    {
        if(is_prime[i] == false)
        {
            prime[k++] = i;
            phi[i] = i-1;
        }
        for(j = 0; j<k && i*prime[j]<maxn; j++)
        {
            is_prime[ i*prime[j] ] = true;
            if(i%prime[j] == 0)
            {
                phi[ i*prime[j] ] = phi[i] * prime[j];
                break;
            }
            else
            {
                phi[ i*prime[j] ] = phi[i] * (prime[j]-1);
            }
        }
    }
}
