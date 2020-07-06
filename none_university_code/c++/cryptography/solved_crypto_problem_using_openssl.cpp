#include "pch.h" // Для VS
#include <iostream>
#include <openssl/dh.h>
#include <memory>

struct DHDeleter {
	void operator()(DH* dh) {
		DH_free(dh);
	}
};

struct BNDeleter {
	void operator()(BIGNUM* bn) {
		BN_free(bn);
	}
};

int main()
{
	const char PrivateKey_A[] = "6e113208f17f79c8616dadc94efed5a9c1963f23b470dd58430523a60cf1d9c37443060044b30512b044c9c258c40679e05b1e628a817fed11ee6dfed929f0498936032d35f6509fc04a28f5927bdeaaec6971da1cf3e834460e0514bc97c6cd99ed88eb0330f0120deb5c650a4d9f871724d64e5832942d56b4be184add6d1eb36c274c6c7cccffce90cf2dd0bc75092d0f05144134d884558d8b5000361c3c4d9e6693a58f44c4f30b2d80102017cf61aad13447c82f865a3e1474f09e8b4ddce10bdfa7f3da6e3355189683409df0b1d934ed1a20d864732315d37b9a43fecc79392ac3e00b11d48df1c9200a0c13853f0aaa3b55dd380bb9486182e3084e";
	const char PublicKey_A[] = "365b636df90b90ff090c70f2ca09c124869d1a59bd665367861ff962d3021b13106713e37d30ab83249f4ef0fc99e6453a1cea5a64d257cac3327c8d3251859dd0819d6d9d96f15f9073169f7193fd93088e568dbce64cc06cb8e1e1c8288b737a60d4e33cc633a1dd783408067aba313834903a8f304e675427d9908627ec2e15caa394c82e5458fcedd16698697e12229e68d43f8671d620bc964ecc7550d66eb360180bb52ea223b51613f2efef8d7f8baeafa60625859db563724876f665884f069ce41351e5c4b81b126209cc1b2683be2499dd76e30687f90bfd7ca23f318e59bfe5f4c01d943c9ac87190e0849092e852684b4ecee4780d8666e24569";
	const char PublicKey_B[] = "16dbc03833b1bac692f7bf47d17dda664f792e91031698ae11ce5a1b2c4c19055bffbafc1a5b0ad53484ff31b132ef7e40caef235b3e45ea34e9b7ec2ea456df0605d7b93e4a8c6e4f73df9c1448d0e91676951c114d3799597066ee1898ff02b3715c10e484cad97c58d76f6c127c0b70acc95c8949374341a003434eee353dcc3dc0796294591248f013a7c5ee61b5a8cfd67b321ef298502af334e70820aeea106b2f5750cad3007b285cbc8732fe423c4d01a402c201405c9acf1c9bb090a4c8a414401fe2f23558e7deb2d17d936028a11058e61dce2093eaffb541d74e82b609a52f9b562ffb4cf6412448ff181953ad0ca0a2492b61aca2e0b2e6ea69";
	const char p[] = "00a7145548118282480a03eb1881de0cf37f3ffd0c6466c2fa95c9ba1bffa789431d1aec63e9aafd7d5a4254a70f9c8f275900b6df519d1f85f3c0d2c632b1fa40be934071ee7859e1c6e37ff95ddd9a0c89a05ad78b54fcfebf73fdeba7166f60593ac735e63d59b254345f703453ccee04012f68ece2d2bff80379627fe3207ec79264892e108565c44084c1f0748cdab1ebd670f67805ed88c9817f2b5ecd36f5842decf23e88a6718361602c85f1d7dd6bd3506af73010c8359453379146b6ba9e00b4f62d138dcca9173f3927ef5db825cdb1b6452f92fcbf838bdc590c1e3e7d7df76549fdf7ca018b6754f725c197bffa376af3089c376d58c4233320a3";
	const char g[] = "2";

	std::unique_ptr<DH, DHDeleter> dh(DH_new()); //Создаем DH и далее передаем в него параметры из задания
	BN_hex2bn(&dh->priv_key, PrivateKey_A);
	BN_hex2bn(&dh->pub_key, PublicKey_A);
	BN_hex2bn(&dh->p, p);
	BN_dec2bn(&dh->g, g);

	BIGNUM *PublicKey_B_BN = nullptr; //Публичный ключ пользователя Б, необходимый для вычисления общего секрета
	BN_dec2bn(&PublicKey_B_BN, PublicKey_B);
	std::unique_ptr<BIGNUM, BNDeleter>PublicKey_B_BN_unique(PublicKey_B_BN);
	int dh_size = DH_size(dh.get());
		
	std::unique_ptr<unsigned char[]> secret = std::make_unique<unsigned char[]>(dh_size);
		int secret_size = DH_compute_key_padded(secret.get(), PublicKey_B_BN_unique.get(), dh.get());//Вычисляем секрет
		
		if (secret_size != -1) {//Если все прошло успешно - выводим его
			for (int i = 0; i < dh_size; ++i) {

				printf("%x", secret[i]);

			}
		}
		else {
			std::cout << "Can't compute key!" << std::endl;
		}
		std::cout << std::endl;
	return 0;
}