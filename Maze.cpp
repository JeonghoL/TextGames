#include <iostream>
#include <conio.h>
#include <time.h>

/*
0 : ��
1 : ��
2 : ������
3 : ������
4 : ��ź
5 : �Ŀ�������
6 : ���б� ������
7 : ���������
8 : ��Ȧ
*/

struct _tagPoint {
	int x;
	int y;
};

// typedef : Ÿ���� �������ϴ� ����̴�.
typedef _tagPoint POINT;
typedef _tagPoint* PPOINT;

typedef struct _tagPlayer {
	_tagPoint tPos;
	bool bWallPush;
	bool bPushOnOff;
	bool bTransparency;
	int iBombPower;
}PLAYER, *PPLAYER;

void SetMaze(char Maze[21][21], PPLAYER pPlayer, PPOINT pStartPos, PPOINT pEndPos);

void Output(char Maze[21][21], PPLAYER pPlayer);

void MovePlayer(char Maze[21][21], PPLAYER pPlayer, char cInput);

void MoveUp(char Maze[21][21], PPLAYER pPlayer);
void MoveDown(char Maze[21][21], PPLAYER pPlayer);

void MoveRight(char Maze[21][21], PPLAYER pPlayer);
void MoveLeft(char Maze[21][21], PPLAYER pPlayer);

// ������ ������ const�� �����ϸ� ����Ű�� ����� ���� ������ �� ����.
void CreateBomb(char Maze[21][21], const PPLAYER pPlayer, PPOINT pBombArr, int* pBombCount);

void Fire(char Maze[21][21], PPLAYER pPlayer, PPOINT pBombArr, int* pBombCount);

bool AddItem(char cItemType, PPLAYER pPlayer);

int main() {
	srand((unsigned int)time(NULL));

	// 20 x 20 �̷θ� ������ش�.
	char strMaze[21][21] = { };

	PLAYER tPlayer = { };
	POINT tStartPos;
	POINT tEndPos;

	tPlayer.iBombPower = 1;

	int iBombCount = 0;

	POINT tBombPos[5];


	// �̷θ� �����Ѵ�.
	SetMaze(strMaze, &tPlayer, &tStartPos, &tEndPos);

	while (true) {
		system("cls");
		// �̷θ� ����Ѵ�.
		Output(strMaze, &tPlayer);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y) {
			std::cout << "�����߽��ϴ�." << std::endl;
			break;
		}

		std::cout << "t : ��ź��ġ u : ��ź ��Ʈ���� i : ���б� ON/OFF" << std::endl;
		std::cout << "w : �� s : �Ʒ� a : ���� d : ������ q : ���� : ";
		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;

		else if (cInput == 't' || cInput == 'T') {
			CreateBomb(strMaze, &tPlayer, tBombPos, &iBombCount);
		}

		else if (cInput == 'u' || cInput == 'U') {
			Fire(strMaze, &tPlayer, tBombPos, &iBombCount);
		}

		else if (cInput == 'i' || 'I') {
			if (tPlayer.bWallPush)
				tPlayer.bPushOnOff = !tPlayer.bPushOnOff;
		}

		else
			MovePlayer(strMaze, &tPlayer, cInput);
	}
}

void SetMaze(char Maze[21][21], PPLAYER pPlayer, PPOINT pStartPos, PPOINT pEndPos) {
	// MazeList.txt ������ �о�ͼ� �̷� ����� �����.
	FILE* pFile = NULL;

	fopen_s(&pFile, "MazeList.txt", "rt");

	char** pMazeList = NULL;

	if (pFile) {
		char cCount;

		fread(&cCount, 1, 1, pFile);

		int iMazeCount = atoi(&cCount);

		fread(&cCount, 1, 1, pFile);

		// char* �迭�� �̷� ������ŭ �Ҵ��Ѵ�.
		pMazeList = new char* [iMazeCount];

		for (int i = 0; i < iMazeCount; ++i) {
			int iNameCount = 0;
			
			// ���� �̷��� ���� �̸��� ������ �迭�� 256���� �Ҵ��صд�.
			// �̸� �˳��ϰ� �Ҵ��ص� ���̴�.
			pMazeList[i] = new char[256];

			while (true) {
				fread(&cCount, 1, 1, pFile);

				if (cCount == '\n') {
					pMazeList[i][iNameCount] = cCount;
					++iNameCount;
				}

				else
					break;
			}
			
			// ���� �̸��� ��� �о��ٸ� ���ڿ��� �������� 0��
			// �־ �� ���ڿ��� ���� �˷��ش�.
			pMazeList[i][iNameCount] = 0;

			std::cout << pMazeList[i] << std::endl;
		}

		fclose(pFile);
	}
	
	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;

	pPlayer->tPos = *pStartPos;

	strcpy_s(Maze[0], "21100000000000000000");
	strcpy_s(Maze[1], "00111111111100000000");
	strcpy_s(Maze[2], "00100010000111111100");
	strcpy_s(Maze[3], "01100010000000000100");
	strcpy_s(Maze[4], "01000011110001111100");
	strcpy_s(Maze[5], "01000000001111000000");
	strcpy_s(Maze[6], "01100000001000000000");
	strcpy_s(Maze[7], "00100000001111111000");
	strcpy_s(Maze[8], "00001110000000001000");
	strcpy_s(Maze[9], "01111011111111111000");
	strcpy_s(Maze[10], "01000000000000000000");
	strcpy_s(Maze[11], "01111100111111100000");
	strcpy_s(Maze[12], "00000111100000111110");
	strcpy_s(Maze[13], "01111100000000000010");
	strcpy_s(Maze[14], "01000000001111111110");
	strcpy_s(Maze[15], "01111110011000000000");
	strcpy_s(Maze[16], "00000010010000000000");
	strcpy_s(Maze[17], "01111110011111000000");
	strcpy_s(Maze[18], "01000000000001100000");
	strcpy_s(Maze[19], "11000000000000111113");
}

void Output(char Maze[21][21], PPLAYER pPlayer) {
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			if (Maze[i][j] == '4')
				std::cout << "��";

			else if (pPlayer->tPos.x == j && pPlayer->tPos.y == i)
				std::cout << "��";

			else if (Maze[i][j] == '0')
				std::cout << "��";

			else if (Maze[i][j] == '1')
				std::cout << "  ";

			else if (Maze[i][j] == '2')
				std::cout << "��";

			else if (Maze[i][j] == '3')
				std::cout << "��";

			else if (Maze[i][j] == '5')
				std::cout << "��";

			else if (Maze[i][j] == '6')
				std::cout << "��";

			else if (Maze[i][j] == '7')
				std::cout << "��";
		}

		std::cout << std::endl;
	}

	std::cout << "��ź �Ŀ� : " << pPlayer->iBombPower << std::endl;
	std::cout << "����� : ";
	if (pPlayer->bTransparency)
		std::cout << "ON\t";
	else
		std::cout << "OFF\t";

	std::cout << "���б� : ";
	if (pPlayer->bWallPush) {
		std::cout << "����" << std::endl;
	
		if (pPlayer->bPushOnOff)
			std::cout << "ON" << std::endl;

		else
			std::cout << "OFF" << std::endl;
	}
	else
		std::cout << "�Ұ��� / OFF" << std::endl;
}

void MovePlayer(char Maze[21][21], PPLAYER pPlayer, char cInput) {
	switch (cInput) {
	case 'w':
	case 'W':
		MoveUp(Maze, pPlayer);
		break;
	case 's':
	case 'S':
		MoveDown(Maze, pPlayer);
		break;
	case 'a':
	case 'A':
		MoveLeft(Maze, pPlayer);
		break;
	case 'd':
	case 'D':
		MoveRight(Maze, pPlayer);
		break;

	}
}

bool AddItem(char cItemType, PPLAYER pPlayer) {
	if (cItemType == '5') {
		if (pPlayer->iBombPower < 5)
			++pPlayer->iBombPower;
	
		return true;
	}

	else if (cItemType == '6') {
		pPlayer->bWallPush = true;
		pPlayer->bPushOnOff = true;
		return true;
	}

	else if (cItemType == '7') {
		pPlayer->bTransparency = true;
		return true;
	}

	return false;
}

void MoveUp(char Maze[21][21], PPLAYER pPlayer) {
	if (pPlayer->tPos.y - 1 >= 0) {
		// ������ üũ�Ѵ�.
		if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '0' &&
			Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '4') {
			--pPlayer->tPos.y;
		}

		// �� �бⰡ �����ϰ� �ٷ� ��ĭ�� ���� ���
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '0') {
			// �� �бⰡ ON ������ ���
			if (pPlayer->bPushOnOff) {
				// ���� ��ĭ�� 0���� ũ�ų� ���� ���� �ε����� �ִٴ� �ǹ�.
				if (pPlayer->tPos.y - 2 >= 0) {
					// ���� ��ĭ�� ���̾�� �бⰡ �����ϴ�. �׷��Ƿ� ������ üũ�Ѵ�.
					if (Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] != '1') {
						// ���� ��ĭ�� ������ �ϰ�
						Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] != '0';
						// ��ĭ�� ���̾��µ� ��� ������ش�.
						Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '1';
						--pPlayer->tPos.y;
					}
				}
			}
		}

		else if (pPlayer->bTransparency)
			--pPlayer->tPos.y;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MoveDown(char Maze[21][21], PPLAYER pPlayer) {
	if (pPlayer->tPos.y + 1 < 20) {
		// ������ üũ�Ѵ�.
		if (Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '0' &&
			Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '4') {
			++pPlayer->tPos.y;
		}
		else if (pPlayer->bTransparency)
			++pPlayer->tPos.y;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MoveRight(char Maze[21][21], PPLAYER pPlayer) {
	if (pPlayer->tPos.x + 1 < 20) {
		// ������ üũ�Ѵ�.
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '0' &&
			Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '4') {
			++pPlayer->tPos.x;
		}
		else if (pPlayer->bTransparency)
			++pPlayer->tPos.x;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MoveLeft(char Maze[21][21], PPLAYER pPlayer) {
	if (pPlayer->tPos.x - 1 >= 0) {
		// ������ üũ�Ѵ�.
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '0' &&
			Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '4') {
			--pPlayer->tPos.x;
		}
		else if (pPlayer->bTransparency)
			--pPlayer->tPos.x;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void CreateBomb(char Maze[21][21], const PPLAYER pPlayer, PPOINT pBombArr, int* pBombCount) {
	if (*pBombCount == 5)
		return;

	else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x] == '0')
		return;

	for (int i = 0; i < *pBombCount; ++i) {
		if (pPlayer->tPos.x == pBombArr[i].x &&
			pPlayer->tPos.y == pBombArr[i].y)
			return;
	}

	pBombArr[*pBombCount] = pPlayer->tPos;
	++(*pBombCount);
	
	Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '4';
}

void Fire(char Maze[21][21], PPLAYER pPlayer, PPOINT pBombArr, int* pBombCount) {
	for (int i = 0; i < *pBombCount; ++i) {
		Maze[pBombArr[i].y][pBombArr[i].x] = '1';

		// �÷��̾ ��ź�� �¾����� ���������� ������.
		if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y) {
			pPlayer->tPos.x = 0;
			pPlayer->tPos.y = 0;
		}
		
		for (int j = 1; j <= pPlayer->iBombPower; ++j) {
			if (pBombArr[i].y - j >= 0) {
				if (Maze[pBombArr[i].y - j][pBombArr[i].x] == '0') {
					// ������ ��� Ȯ���� ���Ѵ�.
					if (rand() % 100 < 20) {
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '5';
						
						else if (iPercent < 80)
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '6';

						else
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '7';
					}
					else
						Maze[pBombArr[i].y - j][pBombArr[i].x] = '1';
				}

				// �÷��̾ ��ź�� �¾����� ���������� ������.
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y - j) {
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].y + j < 20) {
				if (Maze[pBombArr[i].y + j][pBombArr[i].x] == '0') {
					// ������ ��� Ȯ���� ���Ѵ�.
					if (rand() % 100 < 20) {
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '5';

						else if (iPercent < 80)
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '6';

						else
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '7';
					}
					
					else
						Maze[pBombArr[i].y + j][pBombArr[i].x] = '1';
				}

				// �÷��̾ ��ź�� �¾����� ���������� ������.
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y + j) {
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].x - j >= 0) {
				if (Maze[pBombArr[i].y][pBombArr[i].x - j] == '0') {
					// ������ ��� Ȯ���� ���Ѵ�.
					if (rand() % 100 < 20) {
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '5';

						else if (iPercent < 80)
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '6';

						else
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '7';
					}

					else
						Maze[pBombArr[i].y][pBombArr[i].x - j] = '1';
				}

				// �÷��̾ ��ź�� �¾����� ���������� ������.
				if (pPlayer->tPos.x == pBombArr[i].x - j && pPlayer->tPos.y == pBombArr[i].y) {
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].x + j < 20) {
				if (Maze[pBombArr[i].y][pBombArr[i].x + j] == '0') {
					// ������ ��� Ȯ���� ���Ѵ�.
					if (rand() % 100 < 20) {
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '5';

						else if (iPercent < 80)
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '6';

						else
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '7';
					}

					else
						Maze[pBombArr[i].y][pBombArr[i].x + j] = '1';
				}

				// �÷��̾ ��ź�� �¾����� ���������� ������.
				if (pPlayer->tPos.x == pBombArr[i].x + j && pPlayer->tPos.y == pBombArr[i].y) {
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}
		}
	}

	*pBombCount = 0;

}