#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{
	if( DxLib_Init() == -1 )		// ＤＸライブラリ初期化処理
	{
		return -1 ;			// エラーが起きたら直ちに終了
	}

	int AHandle, BHandle, CHandle;
	int SizeX, SizeY;
	int i, j;
	int AColR, AColG, AColB, AColA;
	int BColR, BColG, BColB, BColA;
	int CColR, CColG, CColB, CColA;
	double Alpha = 0.60736;

	BHandle = LoadSoftImage( "B7.png" ) ;
	CHandle = LoadSoftImage( "c83_3.jpg" ) ;

	GetSoftImageSize( BHandle, &SizeX, &SizeY);

	AHandle = MakeXRGB8ColorSoftImage( SizeX, SizeY ) ;

	for (i=0;i<SizeX;i++) {
		for (j=0;j<SizeY;j++) {
			GetPixelSoftImage( BHandle, i, j, &BColR, &BColG, &BColB, &BColA );
			GetPixelSoftImage( CHandle, i, j, &CColR, &CColG, &CColB, &CColA );
			AColR = (int)(( (double)CColR - (double)BColR * (double)BColA / 255.0 * Alpha ) / ( 1.0 - Alpha * (double)BColA / 255.0 ));
			if (AColR>255) AColR=255;
			if (AColR<0) AColR=0;
			AColG = (int)(( (double)CColG - (double)BColG * (double)BColA / 255.0 * Alpha ) / ( 1.0 - Alpha * (double)BColA / 255.0 ));
			if (AColG>255) AColG=255;
			if (AColG<0) AColG=0;
			AColB = (int)(( (double)CColB - (double)BColB * (double)BColA / 255.0 * Alpha ) / ( 1.0 - Alpha * (double)BColA / 255.0 ));
			if (AColB>255) AColB=255;
			if (AColB<0) AColB=0;
			DrawPixelSoftImage( AHandle, i, j, AColR, AColG, AColB, 255 );
			if (i==157 && j==264) {
				i+=0;
			}
		}
	}

	DrawSoftImage( 0, 0, AHandle );

	WaitKey() ;

	InitSoftImage();

	DxLib_End() ;				// ＤＸライブラリ使用の終了処理

	return 0 ;				// ソフトの終了 
}