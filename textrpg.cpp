#include <iostream>
#include <time.h>
#define NAME_SIZE			32
#define ITEM_DESC_LENGTH	512
#define INVENTORY_MAX		20
#define STORE_WEAPON_MAX	3
#define STORE_ARMOR_MAX		3

/*
1. ����������� �Ǹ��� ������ ����� ������ְ� �ش� ����� ������ش�.
2. ����� �� �տ� ��ȣ�� �ο����ְ� ��ȣ�� �Է¹޾Ƽ� �ش� ��ȣ�� ��������
�����ϰ� ���ش�. ���� ������ ��ȣ�� �ڷΰ��� ����� �����.
��, ������ �� á�ų� ���� ������ ��� �������� ���ϰ� �Ѵ�.
3. ������ �����ϸ� ������� �������� �����ش�.
*/

enum MAIN_MENU {
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT
};

enum MAP_TYPE {
	MT_NONE,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_BACK
};

enum JOB {
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_END
};

enum BATTLE {
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK
};

enum ITEM_TYPE {
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};

enum STORE_MENU {
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
};

struct _tagItem {
	char	strName[NAME_SIZE];
	char	strTypeName[NAME_SIZE];
	ITEM_TYPE	eType;
	int		iMin;
	int		iMax;
	int		iPrice;
	int		iSell;
	char	strDesc[ITEM_DESC_LENGTH];
};

struct _tagInventory {
	_tagItem	tItem[INVENTORY_MAX];
	int			iItemCount;
	int			iGold;
};

struct _tagPlayer {
	char	strName[NAME_SIZE];
	char	strJobName[NAME_SIZE];
	JOB		eJob;
	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iExp;
	int		iLevel;
	_tagInventory tInventory;
};

struct _tagMonster {
	char	strName[NAME_SIZE];
	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iLevel;
	int		iExp;
	int		iGoldMin;
	int		iGoldMax;
};

int main() {
	srand((unsigned int)time(0));

	// ������ ������ �� �÷��̾� ������ �����ϰ� �Ѵ�.
	_tagPlayer tPlayer = { };

	// �÷��̾� �̸��� �Է¹޴´�.
	std::cout << "�̸� : ";
	std::cin.getline(tPlayer.strName, NAME_SIZE - 1);

	int iJob = JOB_NONE;
	while (iJob == JOB_NONE) {
		system("cls");
		std::cout << "1. ���" << std::endl;
		std::cout << "2. �ü�" << std::endl;
		std::cout << "3. ������" << std::endl;
		std::cout << "������ �����ϼ��� : ";
		std::cin >> iJob;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1024, '\n');
			continue;
		}

		else if (iJob <= JOB_NONE || iJob >= JOB_END)
			iJob = JOB_NONE;
	}

	tPlayer.iLevel = 1;
	tPlayer.iExp = 0;
	tPlayer.eJob = (JOB)iJob;
	tPlayer.tInventory.iGold = 10000;

	switch (tPlayer.eJob) {
	case JOB_KNIGHT:
		strcpy_s(tPlayer.strJobName, "���");
		tPlayer.iAttackMin = 5;
		tPlayer.iAttackMax = 10;
		tPlayer.iArmorMin = 15;
		tPlayer.iArmorMax = 20;
		tPlayer.iHPMax = 500;
		tPlayer.iHP = 500;
		tPlayer.iMPMax = 100;
		tPlayer.iMP = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(tPlayer.strJobName, "�ü�");
		tPlayer.iAttackMin = 10;
		tPlayer.iAttackMax = 15;
		tPlayer.iArmorMin = 10;
		tPlayer.iArmorMax = 15;
		tPlayer.iHPMax = 400;
		tPlayer.iHP = 400;
		tPlayer.iMPMax = 200;
		tPlayer.iMP = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(tPlayer.strJobName, "������");
		tPlayer.iAttackMin = 15;
		tPlayer.iAttackMax = 20;
		tPlayer.iArmorMin = 5;
		tPlayer.iArmorMax = 10;
		tPlayer.iHPMax = 300;
		tPlayer.iHP = 300;
		tPlayer.iMPMax = 300;
		tPlayer.iMP = 300;
		break;
	}

	// ���͸� �����Ѵ�.
	_tagMonster tMonsterArr[MT_BACK - 1] = { };

	// ��� ����
	strcpy_s(tMonsterArr[0].strName, "���");
	tMonsterArr[0].iAttackMin = 20;
	tMonsterArr[0].iAttackMax = 30;
	tMonsterArr[0].iArmorMin = 2;
	tMonsterArr[0].iArmorMax = 5;
	tMonsterArr[0].iHP = 100;
	tMonsterArr[0].iHPMax = 100;
	tMonsterArr[0].iMP = 10;
	tMonsterArr[0].iMPMax = 10;
	tMonsterArr[0].iLevel = 1;
	tMonsterArr[0].iExp = 1000;
	tMonsterArr[0].iGoldMin = 500;
	tMonsterArr[0].iGoldMax = 1500;

	// Ʈ�� ����
	strcpy_s(tMonsterArr[1].strName, "Ʈ��");
	tMonsterArr[1].iAttackMin = 80;
	tMonsterArr[1].iAttackMax = 130;
	tMonsterArr[1].iArmorMin = 60;
	tMonsterArr[1].iArmorMax = 90;
	tMonsterArr[1].iHP = 2000;
	tMonsterArr[1].iHPMax = 2000;
	tMonsterArr[1].iMP = 100;
	tMonsterArr[1].iMPMax = 100;
	tMonsterArr[1].iLevel = 5;
	tMonsterArr[1].iExp = 7000;
	tMonsterArr[1].iGoldMin = 6000;
	tMonsterArr[1].iGoldMax = 8000;

	// �巡�� ����
	strcpy_s(tMonsterArr[2].strName, "�巡��");
	tMonsterArr[2].iAttackMin = 250;
	tMonsterArr[2].iAttackMax = 500;
	tMonsterArr[2].iArmorMin = 200;
	tMonsterArr[2].iArmorMax = 400;
	tMonsterArr[2].iHP = 30000;
	tMonsterArr[2].iHPMax = 30000;
	tMonsterArr[2].iMP = 20000;
	tMonsterArr[2].iMPMax = 20000;
	tMonsterArr[2].iLevel = 10;
	tMonsterArr[2].iExp = 30000;
	tMonsterArr[2].iGoldMin = 20000;
	tMonsterArr[2].iGoldMax = 50000;

	// �������� �Ǹ��� ������ ����� �����Ѵ�.
	_tagItem tStoreWeapon[STORE_WEAPON_MAX] = { };
	_tagItem tStoreArmor[STORE_ARMOR_MAX] = { };

	// �� ������ �������� �������ش�.

	while (true) {
		system("cls");
		std::cout << "********************** �κ� **********************" << std::endl;
		std::cout << "1. ��" << std::endl;
		std::cout << "2. ����" << std::endl;
		std::cout << "3. ����" << std::endl;
		std::cout << "4. ����" << std::endl;
		std::cout << "�޴��� �����ϼ��� : ";
		int iMenu;
		std::cin >> iMenu;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1024, '\n');
			continue;
		}

		if (iMenu == MM_EXIT)
			break;

		switch (iMenu) {
		case MM_MAP:
			while (true) {
				system("cls");
				std::cout << "********************** �� **********************" << std::endl;
				std::cout << "1. ����" << std::endl;
				std::cout << "2. ����" << std::endl;
				std::cout << "3. �����" << std::endl;
				std::cout << "4. �ڷΰ���" << std::endl;
				std::cout << "���� �����ϼ��� : ";
				std::cin >> iMenu;

				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(1024, '\n');
					continue;
				}

				// �� if���� ���� break�� �� �޴��� �����ֱ� ���� while�� ���� �����Ƿ�
				// �� while���� ����������.

				if (iMenu == MT_BACK)
					break;

				// ������ �޴����� 1�� ���ָ� ���� �迭�� �ε����� �ȴ�.
				// �׷��� �ؼ� �ش� ���� ���͸� �������ش�.
				_tagMonster tMonster = tMonsterArr[iMenu - 1];

				while (true) {
					system("cls");
					switch (iMenu) {
					case MT_EASY:
						std::cout << "********************** ���� **********************" << std::endl;
						break;
					case MT_NORMAL:
						std::cout << "********************** ���� **********************" << std::endl;
						break;
					case MT_HARD:
						std::cout << "********************** ����� **********************" << std::endl;
						break;
					}

					// �÷��̾� ������ ����Ѵ�.
					std::cout << "===================== Player =====================" << std::endl;
					std::cout << "�̸� : " << tPlayer.strName << "\t���� : " <<
						tPlayer.strJobName << std::endl;
					std::cout << "���� : " << tPlayer.iLevel << "\t����ġ : " <<
						tPlayer.iExp << std::endl;
					std::cout << "���ݷ� : " << tPlayer.iAttackMin << " - " <<
						tPlayer.iAttackMax << "\t���� : " << tPlayer.iArmorMin <<
						" - " << tPlayer.iArmorMax << std::endl;
					std::cout << "ü�� : " << tPlayer.iHP << " / " << tPlayer.iHPMax <<
						"\t���� : " << tPlayer.iMP << " / " << tPlayer.iMPMax << std::endl;
					std::cout << "������� : " << tPlayer.tInventory.iGold << " Gold" << std::endl << std::endl;;

					// ���� ���� ���
					std::cout << "===================== Monster =====================" << std::endl;
					std::cout << "�̸� : " << tMonster.strName << "\t���� : "
						<< tMonster.iLevel << std::endl;
					std::cout << "���ݷ� : " << tMonster.iAttackMin << " - " <<
						tMonster.iAttackMax << "\t���� : " << tMonster.iArmorMin <<
						" - " << tMonster.iArmorMax << std::endl;
					std::cout << "ü�� : " << tMonster.iHP << " / " << tMonster.iHPMax <<
						"\t���� : " << tMonster.iMP << " / " << tMonster.iMPMax << std::endl;
					std::cout << "ȹ�����ġ : " << tMonster.iExp << "\tȹ���� : " <<
						tMonster.iGoldMin << " - " << tMonster.iGoldMax << std::endl << std::endl;

					std::cout << "1. ����" << std::endl;
					std::cout << "2. ��������" << std::endl;
					std::cout << "�޴��� �����ϼ��� : ";
					std::cin >> iMenu;

					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(1024, '\t');
						continue;
					}

					else if (iMenu == BATTLE_BACK)
						break;

					switch (iMenu) {
					case BATTLE_ATTACK:
					{
						// ���� ��� Min 5 Max 15 ��� ������ ���
						// 15 - 5 + 1�� �ϸ� 11�� �ȴ�. 11�� ���� �������� 0 ~ 10��
						// ������ �ǰ� ���⿡ Min���� 5�� ���ϰ� �Ǹ�
						// 5 ~ 15 ���̷� ���� ������ �Ǵ°��̴�.
						int iAttack = rand() % (tPlayer.iAttackMax - tPlayer.iAttackMin + 1) +
							tPlayer.iAttackMin;
						int iArmor = rand() % (tMonster.iArmorMax - tMonster.iArmorMin + 1) +
							tMonster.iArmorMin;

						int iDamage = iAttack - iArmor;
						// ���׿����� : ���ǽ� ? true�϶� �� : false�϶� ��;
						iDamage = iDamage < 1 ? 1 : iDamage;

						// ���� HP�� ���ҽ�Ų��.
						tMonster.iHP -= iDamage;

						std::cout << tPlayer.strName << "�� " << tMonster.strName <<
							"���� " << iDamage << " ���ظ� �������ϴ�." << std::endl;

						// ���Ͱ� �׾��� ��츦 ó���Ѵ�.
						if (tMonster.iHP <= 0) {
							std::cout << tMonster.strName << " ���Ͱ� ����Ͽ����ϴ�." << std::endl;

							tPlayer.iExp += tMonster.iExp;
							int iGold = (rand() % (tMonster.iGoldMax - tMonster.iGoldMin + 1) +
								tMonster.iGoldMin);
							tPlayer.tInventory.iGold += iGold;

							std::cout << tMonster.iExp << " ����ġ�� ȹ���Ͽ����ϴ�." << std::endl;
							std::cout << iGold << " Gold�� ȹ���Ͽ����ϴ�." << std::endl;

							tMonster.iHP = tMonster.iHPMax;
							tMonster.iMP = tMonster.iMPMax;
							system("pause");
							break;
						}

						// ���Ͱ� ����ִٸ� �÷��̾ �����Ѵ�.
						iAttack = rand() % (tMonster.iAttackMax - tMonster.iAttackMin + 1) +
							tMonster.iAttackMin;
						iArmor = rand() % (tPlayer.iArmorMax - tPlayer.iArmorMin + 1) +
							tPlayer.iArmorMin;

						iDamage = iAttack - iArmor;
						// ���׿����� : ���ǽ� ? true�϶� �� : false�϶� ��;
						iDamage = iDamage < 1 ? 1 : iDamage;

						// �÷��̾��� HP�� ���ҽ�Ų��.
						tPlayer.iHP -= iDamage;

						std::cout << tMonster.strName << "�� " << tPlayer.strName <<
							"���� " << iDamage << " ���ظ� �������ϴ�." << std::endl;

						// �÷��̾ �׾��� ���
						if (tPlayer.iHP <= 0)
						{
							std::cout << tPlayer.strName << " �÷��̾ ����Ͽ����ϴ�." << std::endl;

							int iExp = tPlayer.iExp * 0.1f;
							int iGold = tPlayer.tInventory.iGold * 0.1f;

							tPlayer.iExp -= iExp;
							tPlayer.tInventory.iGold -= iGold;

							std::cout << iExp << " ����ġ�� �Ҿ����ϴ�." << std::endl;
							std::cout << iGold << " Gold�� �Ҿ����ϴ�." << std::endl;

							// �÷��̾��� HP�� MP�� ȸ���Ѵ�.
							tPlayer.iHP = tPlayer.iHPMax;
							tPlayer.iMP = tPlayer.iMPMax;

						}

						system("pause");
					}
					break;
					}
				}
				break;
		case MM_STORE:
			while (true) {
				system("cls");
				std::cout << "********************** ���� **********************" << std::endl;
				std::cout << "1. �������" << std::endl;
				std::cout << "2. ������" << std::endl;
				std::cout << "3. �ڷΰ���" << std::endl;
				std::cout << "������ �����ϼ��� : ";
				std::cin >> iMenu;

				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(1024, '\n');
					continue;
				}

				else if (iMenu == SM_BACK)
					break;

				switch (iMenu) {
				case SM_WEAPON:
					while (true) {
						system("cls");

						std::cout << "********************** ������� **********************" << std::endl;
						// �Ǹ� ����� �����ش�.
						for (int i = 0; i < STORE_WEAPON_MAX; ++i) {
							std::cout << i + 1 << ". �̸� : " << tStoreWeapon[i].strName <<
								"\t���� : " << tStoreWeapon[i].strTypeName << std::endl;
							std::cout << "���ݷ� : " << tStoreWeapon[i].iMin << " - " <<
								tStoreWeapon[i].iMax << std::endl;
							std::cout << "�ǸŰ��� : " << tStoreWeapon[i].iPrice <<
								"\t���Ű��� : " << tStoreWeapon[i].iSell << std::endl;
							std::cout << "���� : " << tStoreWeapon[i].strDesc << std::endl << std::endl;
						}

						std::cout << STORE_WEAPON_MAX + 1 << ". �ڷΰ���" << std::endl;
						std::cout << "�����ݾ� : " << tPlayer.tInventory.iGold << " Gold" << std::endl;
						std::cout << "�������� : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << std::endl;

						std::cout << "������ �������� �����ϼ��� : ";
						std::cin >> iMenu;

						if (std::cin.fail())
						{
							std::cin.clear();
							std::cin.ignore(1024, '\t');
							continue;
						}

						else if (iMenu == STORE_WEAPON_MAX + 1)
							break;

						else if (iMenu < 1 || iMenu > STORE_WEAPON_MAX + 1) {
							std::cout << "�߸� �����Ͽ����ϴ�." << std::endl;
							system("pause");
							continue;
						}

						// �����ǸŸ�� �迭�� �ε����� �����ش�.
						int iWeaponIndex = iMenu - 1;

						// �κ��丮�� �� á���� �˻��Ѵ�.
						if (tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
							std::cout << "������ �� á���ϴ�." << std::endl;
							system("pause");
							continue;
						}

						// ���� ������ ���
						else if (tPlayer.tInventory.iGold < tStoreWeapon[iWeaponIndex].iPrice) {
							std::cout << "�����ݾ��� �����մϴ�." << std::endl;
							system("pause");
							continue;
						}

						// ó���� iItemCount�� �ϳ��� �߰��Ǿ����� �ʱ� ������ 0���� �ʱ�ȭ
						// �Ǿ� �����Ƿ� 0�� �ε����� ������ �������� �߰��ϰ� �ȴ�. �׸���
						// ī��Ʈ�� 1�� �ȴ�. �������� �߰��� ���� 1�� �ε����� �߰��ϰ� �ȴ�.
						tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] =
							tStoreWeapon[iWeaponIndex];
						++tPlayer.tInventory.iItemCount;

						// ��带 �����Ѵ�.
						tPlayer.tInventory.iGold -= tStoreWeapon[iWeaponIndex].iPrice;

						std::cout << tStoreWeapon[iWeaponIndex].strName << " �������� �����Ͽ����ϴ�." << std::endl;
						system("pause");
					}
					break;
				case SM_ARMOR:
					break;
				}
			}
			break;
		case MM_INVENTORY:
			std::cout << "********************** ���� **********************" << std::endl;
			std::cout << "===================== Player =====================" << std::endl;
			std::cout << "�̸� : " << tPlayer.strName << "\t���� : " <<
				tPlayer.strJobName << std::endl;
			std::cout << "���� : " << tPlayer.iLevel << "\t����ġ : " <<
				tPlayer.iExp << std::endl;
			std::cout << "���ݷ� : " << tPlayer.iAttackMin << " - " <<
				tPlayer.iAttackMax << "\t���� : " << tPlayer.iArmorMin <<
				" - " << tPlayer.iArmorMax << std::endl;
			std::cout << "ü�� : " << tPlayer.iHP << " / " << tPlayer.iHPMax <<
				"\t���� : " << tPlayer.iMP << " / " << tPlayer.iMPMax << std::endl;
			std::cout << "������� : " << tPlayer.tInventory.iGold << " Gold" << std::endl << std::endl;;
			
			for (int i = 0; tPlayer.tInventory.iItemCount; ++i) {
				std::cout << i + 1 << ". �̸� : " << tPlayer.tInventory.tItem[i].strName <<
					"\t���� : " << tPlayer.tInventory.tItem[i].strTypeName << std::endl;
				std::cout << "���ݷ� : " << tPlayer.tInventory.tItem[i].iMin << " - " <<
					tPlayer.tInventory.tItem[i].iMax << std::endl;
				std::cout << "�ǸŰ��� : " << tPlayer.tInventory.tItem[i].iPrice <<
					"\t���Ű��� : " << tPlayer.tInventory.tItem[i].iSell << std::endl;
				std::cout << "���� : " << tPlayer.tInventory.tItem[i].strDesc << std::endl << std::endl;
			}

			system("pause");
			break;
		default:
			std::cout << "�߸� �����ϼ̽��ϴ�." << std::endl;
			break;
			}
		}
	}
}