#include <Novice.h>
#include <cmath>

const char kWindowTitle[] = "LE2D_02_アオヤギ_ガクト_確認課題";

struct Matrix4x4 {
    float m[4][4];
};

// 1.行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2)
{
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = m1.m[i][j] + m2.m[i][j];
        }
    }
    return result;
}

// 2.行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2)
{
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = m1.m[i][j] - m2.m[i][j];
        }
    }
    return result;
}

// 3.行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += m1.m[i][k] * m2.m[k][j];
            }
        }
    }
    return result;
}

// 4.逆行列
Matrix4x4 Inverse(const Matrix4x4& m)
{
    Matrix4x4 result = {};
    float det = 0.0f;

    det = m.m[0][0] * (m.m[1][1] * (m.m[2][2] * m.m[3][3] - m.m[2][3] * m.m[3][2]) - m.m[1][2] * (m.m[2][1] * m.m[3][3] - m.m[2][3] * m.m[3][1]) + m.m[1][3] * (m.m[2][1] * m.m[3][2] - m.m[2][2] * m.m[3][1])) - m.m[0][1] * (m.m[1][0] * (m.m[2][2] * m.m[3][3] - m.m[2][3] * m.m[3][2]) - m.m[1][2] * (m.m[2][0] * m.m[3][3] - m.m[2][3] * m.m[3][0]) + m.m[1][3] * (m.m[2][0] * m.m[3][2] - m.m[2][2] * m.m[3][0])) + m.m[0][2] * (m.m[1][0] * (m.m[2][1] * m.m[3][3] - m.m[2][3] * m.m[3][1]) - m.m[1][1] * (m.m[2][0] * m.m[3][3] - m.m[2][3] * m.m[3][0]) + m.m[1][3] * (m.m[2][0] * m.m[3][1] - m.m[2][1] * m.m[3][0])) - m.m[0][3] * (m.m[1][0] * (m.m[2][1] * m.m[3][2] - m.m[2][2] * m.m[3][1]) - m.m[1][1] * (m.m[2][0] * m.m[3][2] - m.m[2][2] * m.m[3][0]) + m.m[1][2] * (m.m[2][0] * m.m[3][1] - m.m[2][1] * m.m[3][0]));

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            float cofactor = m.m[(i + 1) % 4][(j + 1) % 4] * (m.m[(i + 2) % 4][(j + 2) % 4] * m.m[(i + 3) % 4][(j + 3) % 4] - m.m[(i + 2) % 4][(j + 3) % 4] * m.m[(i + 3) % 4][(j + 2) % 4]) - m.m[(i + 1) % 4][(j + 2) % 4] * (m.m[(i + 2) % 4][(j + 1) % 4] * m.m[(i + 3) % 4][(j + 3) % 4] - m.m[(i + 2) % 4][(j + 3) % 4] * m.m[(i + 3) % 4][(j + 1) % 4]) + m.m[(i + 1) % 4][(j + 3) % 4] * (m.m[(i + 2) % 4][(j + 1) % 4] * m.m[(i + 3) % 4][(j + 2) % 4] - m.m[(i + 2) % 4][(j + 2) % 4] * m.m[(i + 3) % 4][(j + 1) % 4]);

            result.m[j][i] = cofactor / det;
        }
    }

    return result;
}


// 5.転置行列
Matrix4x4 Transpose(const Matrix4x4& m)
{
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = m.m[j][i];
        }
    }
    return result;
}

// 6.単位行列の作成
Matrix4x4 MakeIdentity4x4()
{
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
    return result;
}

static const int kColumnWidth = 60;
static const int kRowHeight = 20;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& m, const char* format)
{
    Novice::ScreenPrintf(x, y, "%s", format);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            Novice::ScreenPrintf(x + j * kColumnWidth, y + i * kRowHeight+20, "%6.02f",
                m.m[i][j]);
        }
    }
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    Matrix4x4 m1 = {
        3.2f, 0.7f, 9.6f, 4.4f,
        5.5f, 1.3f, 7.8f, 2.1f,
        6.9f, 8.0f, 2.6f, 1.0f,
        0.5f, 7.2f, 5.1f, 3.3f
    };

    Matrix4x4 m2 = {
        4.1f, 6.5f, 3.3f, 2.2f,
        8.8f, 0.6f, 9.9f, 7.7f,
        1.1f, 5.5f, 6.6f, 0.0f,
        3.3f, 9.9f, 8.8f, 2.2f
    };

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        ///
        /// ↓更新処理ここから
        ///

        Matrix4x4 resultAdd = Add(m1, m2);
        Matrix4x4 resultMultiply = Multiply(m1, m2);
        Matrix4x4 resultSubtract = Subtract(m1, m2);
        Matrix4x4 InverseM1 = Inverse(m1);
        Matrix4x4 InverseM2 = Inverse(m2);
        Matrix4x4 TransposeM1 = Transpose(m1);
        Matrix4x4 TransposeM2 = Transpose(m2);
        Matrix4x4 Identity = MakeIdentity4x4();

        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理ここから
        ///

        MatrixScreenPrintf(0, 0, resultAdd, "Add");
        MatrixScreenPrintf(0, kRowHeight * 5, resultSubtract, "Subtract");
        MatrixScreenPrintf(0, kRowHeight * 5 * 2, resultMultiply, "Multiply");
        MatrixScreenPrintf(0, kRowHeight * 5 * 3, InverseM1, "inverseM1");
        MatrixScreenPrintf(0, kRowHeight * 5 * 4, InverseM2, "inverseM2");
        MatrixScreenPrintf(kColumnWidth * 5, 0, TransposeM1, "TransposeM1");
        MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5, TransposeM2, "TransposeM2");
        MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5 * 2, Identity, "Identity");

        ///
        /// ↑描画処理ここまで
        ///

        // フレームの終了
        Novice::EndFrame();

        // ESCキーが押されたらループを抜ける
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}
