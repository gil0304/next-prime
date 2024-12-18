#include <iostream>
#include <gmp.h>
using namespace std;

// GMPを使った素数判定関数
bool isPrime(const mpz_t num) {
    return mpz_probab_prime_p(num, 25) > 0; // 確率的素数判定（反復25回）
}

// GMPを使って、次の素数を求める関数
void findNextPrime(mpz_t next_prime, const mpz_t start) {
    mpz_set(next_prime, start);       // 初期値を設定
    mpz_add_ui(next_prime, next_prime, 1); // 最初に +1 する

    while (!isPrime(next_prime)) {
        mpz_add_ui(next_prime, next_prime, 1); // 素数が見つかるまで +1
    }
}

int main() {
    mpz_t base, exponent, result, next_prime;

    // GMP用変数の初期化
    mpz_inits(base, exponent, result, next_prime, NULL);

    // 入力
    cout << "基数を入力してください: ";
    gmp_scanf("%Zd", base);
    cout << "指数を入力してください: ";
    gmp_scanf("%Zd", exponent);

    // 高速べき乗法 (GMP の mpz_pow_ui)
    mpz_pow_ui(result, base, mpz_get_ui(exponent));
    cout << "計算結果: ";
    gmp_printf("%Zd\n", result);

    // 次の素数を求める
    findNextPrime(next_prime, result);
    cout << "入力した数より大きい最小の素数は: ";
    gmp_printf("%Zd\n", next_prime);

    // GMP用変数の解放
    mpz_clears(base, exponent, result, next_prime, NULL);

    return 0;
}
