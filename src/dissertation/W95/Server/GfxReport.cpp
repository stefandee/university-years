//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "GfxReport.h"
#include "MManager.h"
#include "Basepath.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformReport *formReport;
//---------------------------------------------------------------------------
__fastcall TformReport::TformReport(TComponent* Owner)
        : TForm(Owner)
{
  last         = 0;
  screenShotNo = 0;
}
//---------------------------------------------------------------------------

void TformReport::AddValue(float value)
{
  tabel[last] = value;
  last++;
  if (last > MAX_TABEL_SIZE) last = 0;
}
//---------------------------------------------------------------------------

void TformReport::PaintTabel()
{
  int i, first, top;
  int Y10, Y90, X10, X90, xEmbel, yEmbel;
  int lastX, lastY;

  if (last > 0)
  {
    X10 = (10 * paintBox->Width) / 100;
    X90 = (90 * paintBox->Width) / 100;
    Y10 = (10 * paintBox->Height) / 100;
    Y90 = (90 * paintBox->Height) / 100;
    xEmbel = (4 * paintBox->Width) / 100;
    yEmbel = (4 * paintBox->Height) / 100;
    // clear the paintbox
    paintBox->Canvas->Brush->Color = clWhite;
    paintBox->Canvas->Pen->Color   = clBlue;
    paintBox->Canvas->Brush->Style = bsSolid;
    paintBox->Canvas->Rectangle(0, 0, paintBox->Width, paintBox->Height);

    // desenez axele
    paintBox->Canvas->Pen->Color   = clBlack;
    paintBox->Canvas->MoveTo(X10, Y90 + yEmbel);
    paintBox->Canvas->LineTo(X10, Y10);
    paintBox->Canvas->MoveTo(X10 - xEmbel, Y90);
    paintBox->Canvas->LineTo(X90, Y90);
    // gradatiile pe Y
    for(i = 1; i < 10; i++)
    {
      paintBox->Canvas->MoveTo(X10 - Y_GRAD / 2, Y90 - i * (Y90 - Y10)/10);
      paintBox->Canvas->LineTo(X10 + Y_GRAD / 2, Y90 - i * (Y90 - Y10)/10);
    }

    // scriu ce reprezinta axele
    paintBox->Canvas->Font->Color  = clBlue;
    SetBkMode(paintBox->Canvas->Handle, TRANSPARENT);
    paintBox->Canvas->TextOut(
      X10 - paintBox->Canvas->TextWidth(Y_LABEL) / 2,
      0,
      Y_LABEL);
    paintBox->Canvas->TextOut(
      paintBox->Width / 2 - paintBox->Canvas->TextWidth(X_LABEL) / 2,
      paintBox->Height - paintBox->Canvas->TextHeight(X_LABEL),
      X_LABEL);

    switch(tabelStyle)
    {
      case ts_bars    :

        if (last * BAR_WIDTH > X90 - X10)
        {
          first = last - (X90 - X10)/BAR_WIDTH;
        }
        else first = 0;

        paintBox->Canvas->Brush->Color = clRed;
        paintBox->Canvas->Pen->Color   = clRed;
        paintBox->Canvas->Brush->Style = bsSolid;
        paintBox->Canvas->Font->Color  = clBlue;
        SetBkMode(paintBox->Canvas->Handle, TRANSPARENT);

        for(i = 0; i < last - first; i++)
        {
          top = Y90 - (int)((float)(Y90 - Y10) * tabel[i + first] / 100.0);
          paintBox->Canvas->Rectangle(X10 + 1 + i * BAR_WIDTH + 1, top, X10 + (i + 1) * BAR_WIDTH + 1, Y90 - 1);
          paintBox->Canvas->TextOut(X10 + 1 + i * BAR_WIDTH, top - paintBox->Canvas->TextHeight("A"), AnsiString::FormatFloat("0.0", tabel[i + first]) + "%");
          paintBox->Canvas->TextOut(X10 + 1 + i * BAR_WIDTH, Y90 - 1 - paintBox->Canvas->TextHeight("A"), AnsiString(i));
        }

        break;

      case ts_circles :
        break;

      case ts_earthquake    :
      {
        int first, lastX, lastY;

        if (last > (X90 - X10))
        {
          first = last - (X90 - X10);
        }
        else first = 0;

        lastX = X10 + 1;
        lastY = Y90 - 1;

        for(i = 0; i < last - first; i++)
        {
            top = Y90 - (int)((float)(Y90 - Y10) * tabel[i + first] / 100.0);
            paintBox->Canvas->Pen->Color = clRed;
            paintBox->Canvas->MoveTo(lastX, lastY);
            paintBox->Canvas->LineTo(X10 + 1 + i, top);
            lastX = i + X10 + 1;
            lastY = top;
        }

        break;
      }

      case ts_interpolate  :
      {
        float sum;
        int   counter, first;

        if (last > (X90 - X10) * SUM_ELEMENTS)
        {
          first = last - (X90 - X10) * SUM_ELEMENTS;
        }
        else first = 0;

        lastX = X10 + 1;
        lastY = Y90 - 1;
        counter   = 1;
        sum       = 0.0;

        for(i = 0; i < last - first; i++)
        {
          counter++;
          sum += tabel[i + first];
          if (counter >= SUM_ELEMENTS)
          {
            sum     = sum / (float)SUM_ELEMENTS;
            top     = Y90 - (int)((float)(Y90 - Y10) * sum / 100.0);

            paintBox->Canvas->Pen->Color = clRed;
            paintBox->Canvas->MoveTo(lastX, lastY);
            paintBox->Canvas->LineTo(X10 + 1 + i, top);
            lastX = X10 + 1 + i;
            lastY = top;
            paintBox->Canvas->TextOut(X10 + 1 + i, top, AnsiString::FormatFloat("0.0", sum) + "%");

            // fac o linie punctata
            paintBox->Canvas->Pen->Style = psDot;
            paintBox->Canvas->Pen->Color = clBlack;
            paintBox->Canvas->Pen->Width = 1;
            paintBox->Canvas->MoveTo(X10 + 1 + i, top);
            paintBox->Canvas->LineTo(X10 + 1 + i, Y90 - 1);
            paintBox->Canvas->TextOut(X10 + 2 + i, Y90 - 1 - paintBox->Canvas->TextHeight("A"), AnsiString(i));
            paintBox->Canvas->Pen->Style = psSolid;

            sum     = 0.0;
            counter = 1;
          }

        }
        break;
      }
    }
  }
}
//---------------------------------------------------------------------------

void TformReport::SetStyle(TTabelStyles style)
{
  tabelStyle = style;
}
//---------------------------------------------------------------------------

void __fastcall TformReport::FormShow(TObject *Sender)
{
  PaintTabel();
}
//---------------------------------------------------------------------------

void __fastcall TformReport::FormResize(TObject *Sender)
{
  PaintTabel();
}
//---------------------------------------------------------------------------

void __fastcall TformReport::Drawashistogram1Click(TObject *Sender)
{
  Drawashistogram1->Checked = true;
  SetStyle(ts_bars);
}
//---------------------------------------------------------------------------

void __fastcall TformReport::Drawaspints1Click(TObject *Sender)
{
  Drawaspints1->Checked = true;
  SetStyle(ts_interpolate);
}
//---------------------------------------------------------------------------

void __fastcall TformReport::Drawaslines1Click(TObject *Sender)
{
  Drawaspints1->Checked = true;
  SetStyle(ts_earthquake);
}
//---------------------------------------------------------------------------


void __fastcall TformReport::SaveBmpClick(TObject *Sender)
{
  AnsiString fileName = BASE_SHOT_NAME, tempNo = AnsiString(screenShotNo);

  // completez numele shotului cu 0, ca sa arate bine
  if (tempNo.Length() < 3)
  {
    for(int i = 0; i < 3 - tempNo.Length(); i++)
    {
      fileName = fileName + "0";
    }
  }

  fileName = getProgramPath() + fileName + tempNo + ".bmp";

  // salvez bitmapul
  Graphics::TBitmap* tempBmp = new Graphics::TBitmap();
  tempBmp->Width   = paintBox->Width;
  tempBmp->Height  = paintBox->Height;

  try
  {
    BitBlt(tempBmp->Canvas->Handle, 0, 0, tempBmp->Width, tempBmp->Height, paintBox->Canvas->Handle, 0, 0, SRCCOPY);
    tempBmp->SaveToFile(fileName);  
    screenShotNo++;
  }
  catch(...)
  {
  }

  delete tempBmp;
}
//---------------------------------------------------------------------------

