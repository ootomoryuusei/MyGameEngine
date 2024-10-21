//HLSL �n�C���x��(���l�Ԃ��)�V�F�[�f�B���O�����O�G�b�W

//������������������������������������������������������������������������������
// �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D g_texture : register(t0); //�e�N�X�`���[
SamplerState g_sampler : register(s0); //�T���v���[

//������������������������������������������������������������������������������
// �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global
{
    //�ϊ��s��A���_�A����
    float4x4 matWVP; // ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
    
    float4x4 matW; //���[���h�s��
    
    float4 diffuseColor;
    
    bool isTextured;
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
    float4 pos : SV_POSITION; //�ʒu
    float2 uv : TEXCOORD; //UV���W
    float4 cos_alpha : COLOR; //�F�i���邳�j
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
    VS_OUT outData;

	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
    outData.pos = mul(pos, matWVP); 
    outData.uv = uv;
    
    
    float4 light = float4(1,1,-1,0); //�����x�N�g���̋t�x�N�g��
    light = normalize(light); //�P�ʃx�N�g����
    //�@������]
    normal = mul(normal, matW);
    normal = normalize(normal);
    normal.w = 0;
    light.w = 0;
    //outData.color = clamp(dot(normal, light),0,1);
    outData.cos_alpha = clamp(dot(normal, light),0,1);

	//�܂Ƃ߂ďo��
    return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
    //return float4(230.0f/255.0f , 130.0f/255.0f , 238.0f/255.0f, 1); //�s�N�Z����h��F
    //float4 myUV = { 0.125, 0.25, 0, 0 };
    //return g_texture.Sample(g_sampler, myUV);
    //return g_texture.Sample(g_sampler, inData.uv) * inData.color; //�s�N�Z���Ƀe�N�X�`���𒣂�
    
    float4 Id = { 1.0, 1.0, 1.0, 1.0 };
    float4 Kd = g_texture.Sample(g_sampler, inData.uv);
    float cos_alpha = inData.cos_alpha;
    float4 ambentSource = { 0.8, 0.8, 0.8, 0.0 }; //�����̋���
    if (isTextured == false)
    {
        return Id * diffuseColor * cos_alpha + Id * diffuseColor * ambentSource;
    }
    else
    {
        return Id * Kd * cos_alpha + Id * Kd * ambentSource;
    }
    
    //float4 diffuse = g_texture.Sample(g_sampler, inData.uv) * inData.color;
    //float4 ambient = g_texture.Sample(g_sampler, inData.uv) * float4(0.2, 0.2, 0.2, 1);
    //return diffuse + ambient;
   
}