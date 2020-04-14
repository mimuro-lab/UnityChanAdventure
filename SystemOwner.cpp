#include "SystemOwner.h"

/*!
@brief �����鏉�������s��
@date 2020/04/14/23:54
@author mimuro
*/
bool SystemOwner::initialize() const
{
	SetAlwaysRunFlag(TRUE);						//�E�B���h�E���m���A�N�e�B�u�ł����s
	SetWindowSizeChangeEnableFlag(TRUE);		//�E�B���h�E�T�C�Y�����R�ɕύX�ł���悤�ɂ���
	SetOutApplicationLogValidFlag(FALSE);		//���O�o�͂��Ȃ�
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);	//�t���X�N���[�����ɏc������ێ�����
	SetWindowText("�l�����_�^2");				//�E�B���h�E�^�C�g����t����
	ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɕύX
//	SetWindowSizeExtendRate(1.0);				//�E�B���h�E�T�C�Y��ύX���������͂����ɔ{�����w�肷��
	const int COLOR_BIT = 32;					//�F��bit���B�ʏ�32�ŗǂ����y������Ȃ�16�ɂ���
	//SetGraphMode(Define::WIN_W, Define::WIN_H, COLOR_BIT);		//�Q�[����ʂ̉𑜓x��ݒ肷��
	if (DxLib_Init()) {							//DX���C�u��������������
		return false;							//�ُ�I�������瑦���ɂ�߂�
	}
	SetDrawScreen(DX_SCREEN_BACK);				//����ʏ�����ݒ肷��
	return true;
}

/*!
@brief ������I���������s��
@date 2020/04/14/23:54
@author mimuro
*/
bool SystemOwner::finalize() const
{
	DxLib_End();
	return true;
}

/*!
@brief �A�v���̒��S�ƂȂ�֐�
@date 2020/04/14/23:54
@author mimuro
*/
bool SystemOwner::main() const
{
	return true;
}