#include "Transform.h"

// �R���X�g���N�^
Transform::Transform()
{
	pos = VECTOR_ZERO;
	size = VECTOR_ZERO;
	topEdge = VECTOR_ZERO;
	width = 0;
	height = 0;
}

/// <summary>
/// <para>Initialize</para>
/// <para>�I�u�W�F�N�g�������������܂�</para>
/// </summary>
/// <param name="sPos">�����ʒu</param>
/// <param name="sSize">�����T�C�Y</param>
void Transform::Initialize(Vector2* sPos, Vector2* sSize) {
	pos = *sPos;
	size = *sSize;
	CreateEdge();
}

/// <summary>
/// <para>Translate</para>
/// <para>�I�u�W�F�N�g���ړ������܂�</para>
/// </summary>
/// <param name="val">�ړ���</param>
void Transform::Translate(Vector2* val) {
	// ���͒l���Ȃ�
	if (val->x == 0 && val->y == 0)
	{
		// �������Ȃ�
		return;
	}

	// �ړ�
	pos.x += val->x;
	pos.y += val->y;

	// ���_���W�X�V
	CreateEdge();
}

/// <summary>
/// <para>Update</para>
/// <para>�I�u�W�F�N�g�����X�V���܂�</para>
/// </summary>
void Transform::Update() {
	// ���_���W�X�V
	CreateEdge();
}

/// <summary>
/// <para>ExistInScreen</para>
/// <para>�I�u�W�F�N�g����ʓ��ɑ��݂��邩�m�F���܂�</para>
/// </summary>
/// <returns>��ʓ�����</returns>
bool Transform::ExistInScreen() {
	
	//�㕔�̒��_���W����ʓ��ɂ��邩
	if (topEdge.y < WIN_H) {
		return true;
	}
	return false;

}

/// <summary>
/// <para>GetTransform</para>
/// <para>Transform���̃|�C���^���擾���܂�</para>
/// </summary>
/// <returns>�|�C���^</returns>
Transform* Transform::GetTransform() {
	return this;
}

/// <summary>
/// <para>GetEdgeListPtr</para>
/// <para>���_���W�̔z��擪�|�C���^���擾���܂�</para>
/// </summary>
/// <returns>�z��̐擪�|�C���^</returns>
Vector2* Transform::GetTopEdgePtr() {
	return &topEdge;
}

/// <summary>
/// <para>GetWidth</para>
/// <para>�I�u�W�F�N�g�̉������擾���܂�</para>
/// </summary>
/// <returns>����</returns>
float Transform::GetWidth() {
	return width;
}

/// <summary>
/// <para>GetHeight</para>
/// <para>�I�u�W�F�N�g�̏c�����擾���܂�</para>
/// </summary>
/// <returns>�c��</returns>
float Transform::GetHeight() {
	return height;
}

/// <summary>
/// <para>CreateEdge</para>
/// <para>�ݒ肳�ꂽ�ʒu�A�傫�����璸�_���W���Z�o���܂�</para>
/// </summary>
void Transform::CreateEdge() {
	// �I�u�W�F�N�g���擾
	width = size.x * OBJECT_SIZE;
	height = size.y * OBJECT_SIZE;
	
	// ���_���W�擾
	topEdge = *pos.Sub((width / HALF), (height / HALF));
}