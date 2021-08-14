#include "FreeImage.h"
#pragma comment(lib, "FreeImage.lib")
#include <string>
#include <iostream>
#define SHOW(a) 
#ifdef _DEBUG cout << a << endl
#else 1==1;
#endif // _DEBUG

#define magnification 12
#define darken 1.5
#define TRIGGER 20

using namespace std;
int main()
{
	FreeImage_Initialise(TRUE);
	string myPic;
	cin >> myPic;
	SHOW(FreeImage_GetFileType(myPic.c_str(), myPic.size()));
	FIBITMAP* pPIC = FreeImage_Load(FreeImage_GetFileType(myPic.c_str(), myPic.size()), myPic.c_str());
	SHOW(FreeImage_GetColorType(pPIC));
	unsigned W = FreeImage_GetWidth(pPIC);
	unsigned H = FreeImage_GetHeight(pPIC);
	unsigned BPP = FreeImage_GetBPP(pPIC);
	SHOW(W);
	SHOW(H);

	FIBITMAP* pNewPIC = FreeImage_Allocate(W * magnification, H * magnification, BPP, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
	
	for (unsigned y = 0; y < H; y++)
	{
		
		for (unsigned No1 = 0; No1 < magnification; No1++)
		{
			for (unsigned x = 0; x < W; x++)
			{
				RGBQUAD RGB;
				FreeImage_GetPixelColor(pPIC, x, y, &RGB);
				RGB.rgbBlue /= darken;
				RGB.rgbGreen /= darken;
				RGB.rgbRed /= darken;
				for (unsigned No2 = 0; No2 < magnification; No2++)
				{
					FreeImage_SetPixelColor(pNewPIC, x * magnification + No2, y * magnification + No1, &RGB);

				}
			}
	
		}

	}

	FIBITMAP* pScript[5];
	string file[5] = { "Æß.jpg","Ï¦.jpg" ,"¿ì.jpg" ,"ÀÖ.jpg" ,"ßÉ.jpg" };
	for (unsigned i = 0; i < 5; i++)
		pScript[i] = FreeImage_Load(FreeImage_GetFileType(file[i].c_str(), file[i].size()), file[i].c_str());
	unsigned count = 0;
	for (unsigned Y = 0; Y < H; Y++)
	{
		for (unsigned X = 0; X < W; X++)
		{
			for(unsigned y=0;y<magnification;y++)
				for (unsigned x = 0; x < magnification; x++)
				{
					RGBQUAD SC;
					FreeImage_GetPixelColor(pScript[count % 5], x, y, &SC);
					if ((SC.rgbBlue <= TRIGGER) && (SC.rgbRed <= TRIGGER) && (SC.rgbGreen <= TRIGGER))
					{
						RGBQUAD RGB;
						FreeImage_GetPixelColor(pPIC, X, Y, &RGB);
						FreeImage_SetPixelColor(pNewPIC, X * magnification + x, Y * magnification + y, &RGB);
					}
				}
			count++;
		}
	}

	if (FreeImage_Save(FreeImage_GetFileType(myPic.c_str(), myPic.size()), pNewPIC, ("new_" + myPic).c_str(), 0))
	{
		cout << "Succeed in transfrom." << endl;
	}
	else
		cout << "Transfrom error!" << endl;

	for(unsigned i=0;i<5;i++)
		FreeImage_Unload(pScript[i]);
	FreeImage_Unload(pNewPIC);
	FreeImage_Unload(pPIC);
	FreeImage_DeInitialise();
	return 0;
}