// license:BSD-3-Clause
// copyright-holders:Chris Kirmse, Mike Haaland, Ren� Single, Mamesick

#include "winui.h"
#include <setjmp.h>
#include "libjpeg/jpeglib.h"

/***************************************************************************
    function prototypes
***************************************************************************/

typedef struct _mybitmapinfo
{
	int bmWidth;
	int bmHeight;
	int bmColors;
} MYBITMAPINFO, *LPMYBITMAPINFO;

static bool AllocatePNG(png_info *p, HGLOBAL *phDIB, HPALETTE* pPal);
static bool png_read_bitmap_gui(util::core_file &mfile, HGLOBAL *phDIB, HPALETTE *pPAL);
static bool jpeg_read_bitmap_gui(util::core_file &mfile, HGLOBAL *phDIB, HPALETTE *pPAL);
static bool LoadDIB(const char *filename, HGLOBAL *phDIB, HPALETTE *pPal, int pic_type);
static HBITMAP DIBToDDB(HDC hDC, HANDLE hDIB, LPMYBITMAPINFO desc);

/***************************************************************************
    Static global variables
***************************************************************************/

/* these refer to the single image currently loaded by the ScreenShot functions */
static HGLOBAL m_hDIB = NULL;
static HPALETTE m_hPal = NULL;
static HANDLE m_hDDB = NULL;
static int current_image_game = -1;
static int current_image_type = -1;

/* PNG variables */
static int copy_size = 0;
static char* pixel_ptr = 0;
static int row = 0;
static int effWidth = 0;

/***************************************************************************
    Functions
***************************************************************************/

bool ScreenShotLoaded(void)
{
	return m_hDDB != NULL;
}

/* Allow us to pre-load the DIB once for future draws */
bool LoadScreenShot(int nGame, int nType)
{
	/* No need to reload the same one again */
	if (nGame == current_image_game && nType == current_image_type)
		return true;

	/* Delete the last ones */
	FreeScreenShot();
	/* Load the DIB */
	bool loaded = LoadDIB(GetDriverGameName(nGame), &m_hDIB, &m_hPal, nType);

	/* If not loaded, see if there is a clone and try that */
	if (!loaded)
	{
		int nParentIndex = GetParentIndex(&driver_list::driver(nGame));

		if( nParentIndex >= 0)
		{
			loaded = LoadDIB(GetDriverGameName(nParentIndex), &m_hDIB, &m_hPal, nType);
			nParentIndex = GetParentIndex(&driver_list::driver(nParentIndex));

			if (!loaded && nParentIndex >= 0)
				loaded = LoadDIB(GetDriverGameName(nParentIndex), &m_hDIB, &m_hPal, nType);
		}
	}

	if (loaded)
	{
		HDC hDc = GetDC(GetMainWindow());
		m_hDDB = DIBToDDB(hDc, m_hDIB, NULL);
		ReleaseDC(GetMainWindow(), hDc);
		current_image_game = nGame;
		current_image_type = nType;
	}

	return (loaded) ? true : false;
}

HANDLE GetScreenShotHandle()
{
	return m_hDDB;
}

int GetScreenShotWidth(void)
{
	return abs( ((LPBITMAPINFO)m_hDIB)->bmiHeader.biWidth);
}

int GetScreenShotHeight(void)
{
	return abs( ((LPBITMAPINFO)m_hDIB)->bmiHeader.biHeight);
}

/* Delete the HPALETTE and Free the HDIB memory */
void FreeScreenShot(void)
{
	if (m_hDIB != NULL)
		GlobalFree(m_hDIB);

	m_hDIB = NULL;

	if (m_hPal != NULL)
		DeletePalette(m_hPal);

	m_hPal = NULL;

	if (m_hDDB != NULL)
		DeleteObject(m_hDDB);

	m_hDDB = NULL;
	current_image_game = -1;
	current_image_type = -1;
}

static osd_file::error OpenDIBFile(const char *dir_name, const char *zip_name, const std::string &filename, util::core_file::ptr &file, void **buffer)
{
	util::archive_file::error ziperr = util::archive_file::error::NONE;
	util::archive_file::ptr zip;

	// clear out result
	file = nullptr;

	// look for the raw file
	string fname = string(dir_name).append(PATH_SEPARATOR).append(filename);
	osd_file::error filerr = util::core_file::open(fname, OPEN_FLAG_READ, file);

	// did the raw file not exist?
	if (filerr != osd_file::error::NONE)
	{
		// look into zip file
		fname = std::string(dir_name).append(PATH_SEPARATOR).append(zip_name).append(".zip");
		ziperr = util::archive_file::open_zip(fname, zip);

		if (ziperr == util::archive_file::error::NONE)
		{
			int found = zip->search(filename, false);

			if (found >= 0)
			{
				*buffer = malloc(zip->current_uncompressed_length());
				ziperr = zip->decompress(*buffer, zip->current_uncompressed_length());

				if (ziperr == util::archive_file::error::NONE)
					filerr = util::core_file::open_ram(*buffer, zip->current_uncompressed_length(), OPEN_FLAG_READ, file);
			}

			zip.reset();
		}
	}

	if ((filerr != osd_file::error::NONE) || (ziperr != util::archive_file::error::NONE))
	{
		// look into 7z file
		fname = std::string(dir_name).append(PATH_SEPARATOR).append(zip_name).append(".7z");
		ziperr = util::archive_file::open_7z(fname, zip);

		if (ziperr == util::archive_file::error::NONE)
		{
			int found = zip->search(filename, false);

			if (found >= 0)
			{
				*buffer = malloc(zip->current_uncompressed_length());
				ziperr = zip->decompress(*buffer, zip->current_uncompressed_length());

				if (ziperr == util::archive_file::error::NONE)
					filerr = util::core_file::open_ram(*buffer, zip->current_uncompressed_length(), OPEN_FLAG_READ, file);
			}

			zip.reset();
		}
	}

	return filerr;
}

static bool LoadDIB(const char *filename, HGLOBAL *phDIB, HPALETTE *pPal, int pic_type)
{
	osd_file::error filerr = osd_file::error::NOT_FOUND;
	util::core_file::ptr file;
	bool success = false;
	const char *dir_name = NULL;
	const char *zip_name = NULL;
	void *buffer = NULL;
	std::string fname;

	// FILE *p;	
	// p=fopen("log.txt","wt");

	if (pPal != NULL ) 
		DeletePalette(pPal);

	switch (pic_type)
	{
		case TAB_SCREENSHOT:
			dir_name = GetImgDir();
			zip_name = "snap";
			break;

		case TAB_FLYER:
			dir_name = GetFlyerDir();
			zip_name = "flyers";
			break;

		case TAB_CABINET:
			dir_name = GetCabinetDir();
			zip_name = "cabinets";
			break;

		case TAB_MARQUEE:
			dir_name = GetMarqueeDir();
			zip_name = "marquees";
			break;

		case TAB_TITLE:
			dir_name = GetTitlesDir();
			zip_name = "titles";
			break;

		case TAB_CONTROL_PANEL:
			dir_name = GetControlPanelDir();
			zip_name = "cpanel";
			break;

		case TAB_PCB:
			dir_name = GetPcbDir();
		    zip_name = "pcb";
			break;

		case TAB_SCORES:
			dir_name = GetScoresDir();
			zip_name = "scores";
			break;

		case TAB_BOSSES:
			dir_name = GetBossesDir();
			zip_name = "bosses";
			break;

		case TAB_VERSUS:
			dir_name = GetVersusDir();
			zip_name = "versus";
			break;

		case TAB_ENDS:
			dir_name = GetEndsDir();
			zip_name = "ends";
			break;

		case TAB_GAMEOVER:
			dir_name = GetGameOverDir();
			zip_name = "gameover";
			break;

		case TAB_HOWTO:
			dir_name = GetHowToDir();
			zip_name = "howto";
			break;

		case TAB_SELECT:
			dir_name = GetSelectDir();
			zip_name = "select";
			break;

		case TAB_LOGO:
			dir_name = GetLogoDir();
			zip_name = "logo";
			break;

		case TAB_ARTWORK:
			dir_name = GetArtworkDir();
			zip_name = "artpreview";
			break;

		default :
			// shouldn't get here
			return false;
	}

	string ext;
	char *system_name = 0;
	char *file_name = 0;
	int i,j;
	bool ok = FALSE; // TRUE indicates split success

	// allocate space
	system_name = (char*)malloc(strlen(filename) + 1);
	file_name = (char*)malloc(strlen(filename) + 1);

	// if the filename contains a system, split them

	// get system = find colon and truncate there
	for (i = 0; filename[i] && !ok; i++)
	{
		if (filename[i] != ':')
			system_name[i] = filename[i];
		else
		{
			ok = TRUE;
			system_name[i] = '\0';
		}
	}
	system_name[i] = '\0'; // 'i' is one more here than above but needed if no colon

	// now left-justify the filename
	if (ok)
	{
		for (j = 0; filename[i]; j++,i++)
			file_name[j] = filename[i];
		file_name[j] = '\0';
	}
	else
	// it wasn't a software title, copy over to get around const nonsense
	{
		for (i = 0; filename[i]; i++)
			file_name[i] = filename[i];
		file_name[i] = '\0';
	}

	for (u8 extnum = 0; extnum < 3; extnum++)
	{
		switch (extnum)
		{
			case 1:
				ext = ".jpg";
				break;
			case 2:
				ext = ".jpeg";
				break;
			default:
				ext = ".png";
		}

		char* dir_name1 = 0;
		dir_name1 = (char*)malloc(strlen(dir_name) + 2);
		for (i = 0; dir_name[i]; i++)
			dir_name1[i] = dir_name[i];
		dir_name1[i++] = ';';
		dir_name1[i] = '\0';

		// Support multiple paths
		char* dir_one = strtok(dir_name1, ";");

		//Add handling for the displaying of all the different supported snapshot patterntypes
		while (dir_one && filerr != osd_file::error::NONE)
		{
			// Try dir/system.png
			if (filerr != osd_file::error::NONE)
			{
				fname = std::string(system_name).append(ext);
				filerr = OpenDIBFile(dir_one, zip_name, fname, file, &buffer);
			}

			if (filerr != osd_file::error::NONE) 
			{
				//%g/%g
				fname = std::string(file_name).append(PATH_SEPARATOR).append(file_name).append(ext);
				filerr = OpenDIBFile(dir_one, zip_name, fname, file, &buffer);
			}

			// For SNAPS only, try filenames with 0000.
			if ((pic_type == TAB_SCREENSHOT) && (extnum == 0))
			{
				if (filerr != osd_file::error::NONE) 
				{
					//%g/%i
					fname = std::string(system_name).append(PATH_SEPARATOR).append("0000.png");
					filerr = OpenDIBFile(dir_one, zip_name, fname, file, &buffer);
				}
			}

			dir_one = strtok(NULL, ";");
		}

		free(dir_name1);

		// fprintf(p,"fileopen\n");

		if (filerr == osd_file::error::NONE) 
		{
			if (extnum)
				success = jpeg_read_bitmap_gui(*file, phDIB, pPal);
			else
			{
				// fprintf(p,"png read start\n");
				
				success = png_read_bitmap_gui(*file, phDIB, pPal);
			}
			file.reset();
		}
		if (success)
			break;
	}

	// free the buffer if we have to
	if (buffer) 
		free(buffer);

	free(system_name);
	free(file_name);

	// fprintf(p,"png read success");
	// fclose(p);

	return success;
}

static HBITMAP DIBToDDB(HDC hDC, HANDLE hDIB, LPMYBITMAPINFO desc)
{
	BITMAPINFO *bmInfo = (LPBITMAPINFO)hDIB;
	LPVOID lpDIBBits = 0;

	LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)hDIB;
	int nColors = lpbi->biClrUsed ? lpbi->biClrUsed : 1 << lpbi->biBitCount;

	if (bmInfo->bmiHeader.biBitCount > 8)
		lpDIBBits = (LPVOID)((LPDWORD)(bmInfo->bmiColors + bmInfo->bmiHeader.biClrUsed) +
			((bmInfo->bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
	else
		lpDIBBits = (LPVOID)(bmInfo->bmiColors + nColors);

	if (desc != 0)
	{
		/* Store for easy retrieval later */
		desc->bmWidth  = bmInfo->bmiHeader.biWidth;
		desc->bmHeight = bmInfo->bmiHeader.biHeight;
		desc->bmColors = (nColors <= 256) ? nColors : 0;
	}

	HBITMAP hBM = CreateDIBitmap(hDC,				/* handle to device context */
		(LPBITMAPINFOHEADER)lpbi, 					/* pointer to bitmap info header  */
		(long)CBM_INIT, 		  					/* initialization flag */
		lpDIBBits,									/* pointer to initialization data  */
		(LPBITMAPINFO)lpbi, 	  					/* pointer to bitmap info */
		DIB_RGB_COLORS);		  					/* color-data usage  */

	return hBM;
}

/***************************************************************************
    PNG graphics handling functions
***************************************************************************/

static void store_pixels(uint8_t *buf, int len)
{
	if (pixel_ptr && copy_size)
	{
		memcpy(&pixel_ptr[row * effWidth], buf, len);
		row--;
		copy_size -= len;
	}
}

bool AllocatePNG(png_info *p, HGLOBAL *phDIB, HPALETTE *pPal)
{
	BITMAPINFOHEADER bi;
	int nColors = 0;
	row = p->height - 1;
	int lineWidth = p->width;

	if (p->color_type != 2 && p->num_palette <= 256)
		nColors =  p->num_palette;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = p->width;
	bi.biHeight = p->height;
	bi.biPlanes = 1;
	bi.biBitCount = (p->color_type == 3) ? 8 : 24; /* bit_depth; */
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = nColors;
	bi.biClrImportant = nColors;

	effWidth = (long)(((long)lineWidth*bi.biBitCount + 31) / 32) * 4;
	int dibSize = (effWidth * bi.biHeight);
	HGLOBAL hDIB = GlobalAlloc(GMEM_FIXED, bi.biSize + (nColors * sizeof(RGBQUAD)) + dibSize);

	if (!hDIB)
		return false;

	LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)hDIB;
	memcpy(lpbi, &bi, sizeof(BITMAPINFOHEADER));
	RGBQUAD *pRgb = (RGBQUAD*)((char *)lpbi + bi.biSize);
	LPVOID lpDIBBits = (LPVOID)((char *)lpbi + bi.biSize + (nColors * sizeof(RGBQUAD)));

	if (nColors)
	{
		/* Convert a PNG palette (3 byte RGBTRIPLEs) to a new color table (4 byte RGBQUADs) */
		for (int i = 0; i < nColors; i++)
		{
			RGBQUAD rgb;

			rgb.rgbRed = p->palette[i * 3 + 0];
			rgb.rgbGreen = p->palette[i * 3 + 1];
			rgb.rgbBlue = p->palette[i * 3 + 2];
			rgb.rgbReserved = (uint8_t)0;
			pRgb[i] = rgb;
		}
	}

	LPBITMAPINFO bmInfo = (LPBITMAPINFO)hDIB;

	/* Create a halftone palette if colors > 256. */
	if (nColors == 0 || nColors > 256)
	{
		HDC hDC = CreateCompatibleDC(0); /* Desktop DC */
		*pPal = CreateHalftonePalette(hDC);
		DeleteDC(hDC);
	}
	else
	{
		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
		LOGPALETTE *pLP = (LOGPALETTE *)malloc(nSize);

		pLP->palVersion 	= 0x300;
		pLP->palNumEntries	= nColors;

		for (int i = 0; i < nColors; i++)
		{
			pLP->palPalEntry[i].peRed	= bmInfo->bmiColors[i].rgbRed;
			pLP->palPalEntry[i].peGreen = bmInfo->bmiColors[i].rgbGreen;
			pLP->palPalEntry[i].peBlue	= bmInfo->bmiColors[i].rgbBlue;
			pLP->palPalEntry[i].peFlags = 0;
		}

		*pPal = CreatePalette(pLP);
		free(pLP);
	}

	copy_size = dibSize;
	pixel_ptr = (char*)lpDIBBits;
	*phDIB = hDIB;
	return true;
}

/* Copied and modified from png.c */
static bool png_read_bitmap_gui(util::core_file &mfile, HGLOBAL *phDIB, HPALETTE *pPAL)
{
	png_info p;
	UINT i = 0;

	// FILE *p1;
	// p1=fopen("pngread.txt","wt");

	if (p.read_file(mfile) != PNGERR_NONE)
	{

		return false;
	}

	if (p.color_type != 3 && p.color_type != 2)
	{
		// fprintf(p1,"PNG Unsupported color type %i (has to be 2 or 3)\n", p.color_type);
		// fclose(p1);

		//return false;
	}
	if (p.interlace_method != 0)
	{
		// fprintf(p1,"PNG Interlace unsupported\n");
		// fclose(p1);
		return false;
	}
	/* Convert < 8 bit to 8 bit */
	p.expand_buffer_8bit();

	if (!AllocatePNG(&p, phDIB, pPAL))
	{
		// fprintf(p1,"PNG Unable to allocate memory to display screenshot\n");
		// fclose(p1);
		return false;
	}

	int bytespp = (p.color_type == 2) ? 3 : 1;

	for (i = 0; i < p.height; i++)
	{
		UINT8 *ptr = &p.image[i * (p.width * bytespp)];

		if (p.color_type == 2) /*(p->bit_depth > 8) */
		{
			for (int j = 0; j < p.width; j++)
			{
				uint8_t bTmp = ptr[0];
				ptr[0] = ptr[2];
				ptr[2] = bTmp;
				ptr += 3;
			}
		}

		store_pixels(&p.image[i * (p.width * bytespp)], p.width * bytespp);
	}

	// fprintf(p1,"success\n");
	// fclose(p1);

	return true;
}

/***************************************************************************
    JPEG graphics handling functions
***************************************************************************/

struct mameui_jpeg_error_mgr
{
	struct jpeg_error_mgr pub; /* "public" fields */
	jmp_buf setjmp_buffer; /* for return to caller */
};

METHODDEF(void) mameui_jpeg_error_exit(j_common_ptr cinfo)
{
	mameui_jpeg_error_mgr* myerr = (mameui_jpeg_error_mgr*)cinfo->err;
	(*cinfo->err->output_message) (cinfo);
	longjmp(myerr->setjmp_buffer, 1);
}

static bool jpeg_read_bitmap_gui(util::core_file &mfile, HGLOBAL *phDIB, HPALETTE *pPAL)
{
	uint64_t bytes = mfile.size();
	unsigned char* content = (unsigned char*)::malloc(bytes * sizeof(unsigned char));
	::memcpy(content, mfile.buffer(), bytes);

	*pPAL = NULL;
	HGLOBAL hDIB = NULL;
	jpeg_decompress_struct info;
	mameui_jpeg_error_mgr  err;
	info.err = jpeg_std_error(&err.pub);
	err.pub.error_exit = mameui_jpeg_error_exit;

	if (setjmp(err.setjmp_buffer))
	{
		jpeg_destroy_decompress(&info);
		::free(content);
		copy_size = 0;
		pixel_ptr = NULL;
		effWidth = 0;
		row = 0;
		if (hDIB)
			::GlobalFree(hDIB);
		return false;
	}

	jpeg_create_decompress(&info);
	jpeg_mem_src(&info, content, bytes);
	jpeg_read_header(&info, TRUE);
	if (info.num_components != 3 || info.out_color_space != JCS_RGB)
	{
		jpeg_destroy_decompress(&info);
		::free(content);
		return false;
	}

	BITMAPINFOHEADER bi;
	LPBITMAPINFOHEADER lpbi;
	LPVOID lpDIBBits = 0;
	int lineWidth = 0;
	LPSTR pRgb;
	copy_size = 0;
	pixel_ptr = NULL;
	row = info.image_height;
	lineWidth = info.image_width;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = info.image_width;
	bi.biHeight = -info.image_height; //top down bitmap
	bi.biPlanes = 1;
	bi.biBitCount = 24;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 2835;
	bi.biYPelsPerMeter = 2835;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	effWidth = (long)(((long)lineWidth*bi.biBitCount + 31) / 32) * 4;
	int dibSize = (effWidth * info.image_height);
	hDIB = ::GlobalAlloc(GMEM_FIXED, bi.biSize + dibSize);

	if (!hDIB)
	{
		::free(content);
		return false;
	}

	jpeg_start_decompress(&info);

	lpbi = (LPBITMAPINFOHEADER)hDIB;
	::memcpy(lpbi, &bi, sizeof(BITMAPINFOHEADER));
	pRgb = (LPSTR)lpbi + bi.biSize;
	lpDIBBits = (LPVOID)((LPSTR)lpbi + bi.biSize);

	while (info.output_scanline < info.output_height) // loop
	{
		unsigned char* cacheRow[1] = { (unsigned char*)pRgb };
		jpeg_read_scanlines(&info, cacheRow, 1);
		//rgb to win32 bgr
		for (JDIMENSION i = 0; i < info.output_width; ++i)
			std::swap(cacheRow[0][i * 3 + 0], cacheRow[0][i * 3 + 2]);
		pRgb += effWidth;
	}
	jpeg_finish_decompress(&info);
	jpeg_destroy_decompress(&info);
	copy_size = dibSize;
	pixel_ptr = (char*)lpDIBBits;
	*phDIB = hDIB;
	return true;
}

