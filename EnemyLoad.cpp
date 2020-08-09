#include "EnemyLoad.h"

EnemyType EnemyLoad::getType(int _readValue)
{
	switch (_readValue) {
	case 0:
		return EnemyType::Enemy1;
		break;
	case 1:
		return EnemyType::Enemy2;
		break;
	}
	return EnemyType::_end;
}

bool EnemyLoad::getAlive(int _readValue)
{
	if (_readValue == 1)
		return true;
	if (_readValue == 0)
		return false;

	return true;
}

EnemyLoad::EnemyLoad()
{


	FILE* fp;
	fopen_s(&fp, "Stage/Enemy/sample_enemy.csv", "r");

	if (fp == NULL) {

		("ファイルが開けませんでした(in StageLoad::loadCsv)");
		exit(1);
	}

	string csvCell = {};

	int cellEnemy[5] = {};

	int ind = 0;

	while (!feof(fp)) {
		int getf = fgetc(fp);

		// 座標の更新
		if (getf == ',') {// ，だったら座標xを一つ増やす
			//int l = stoi(csvCell);
			cellEnemy[ind] = stoi(csvCell);
			ind++;
			csvCell.clear();
		}
		else if (getf == '\n') {// 改行だったら座標yを一つ増やす
			EnemyElement ele;
			ele.type = getType(cellEnemy[0]);
			ele.x = cellEnemy[1];
			ele.y = cellEnemy[2];
			ele.isAlive = getAlive(cellEnemy[3]);
			ele.hitPoint = cellEnemy[4];
			elements.push_back(ele);
			ind = 0;
		}
		else {// ，でも改行でもない時、要素を読み込んだという事なので、
			
			char value;

			value = getf;

			csvCell.push_back(value);

		}
	}

	fclose(fp);
}