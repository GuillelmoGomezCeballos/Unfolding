void SetStyle() {

  TStyle *TDRStyle = new TStyle("TDR-Style","The Perfect Style for Plots ;-)");
  gStyle = TDRStyle;

  // Canvas

  TDRStyle->SetCanvasColor     (0);
  TDRStyle->SetCanvasBorderSize(10);
  TDRStyle->SetCanvasBorderMode(0);
  TDRStyle->SetCanvasDefH      (700);
  TDRStyle->SetCanvasDefW      (700);
  TDRStyle->SetCanvasDefX      (100);
  TDRStyle->SetCanvasDefY      (100);

  // Pads

  TDRStyle->SetPadColor       (0);
  TDRStyle->SetPadBorderSize  (10);
  TDRStyle->SetPadBorderMode  (0);
  TDRStyle->SetPadBottomMargin(0.13);
  TDRStyle->SetPadTopMargin   (0.08);
  TDRStyle->SetPadLeftMargin  (0.15);
  TDRStyle->SetPadRightMargin (0.05);
  TDRStyle->SetPadGridX       (0);
  TDRStyle->SetPadGridY       (0);
  TDRStyle->SetPadTickX       (0);
  TDRStyle->SetPadTickY       (0);

  // Frames

  TDRStyle->SetFrameFillStyle ( 0);
  TDRStyle->SetFrameFillColor ( 0);
  TDRStyle->SetFrameLineColor ( 1);
  TDRStyle->SetFrameLineStyle ( 0);
  TDRStyle->SetFrameLineWidth ( 1);
  TDRStyle->SetFrameBorderSize(10);
  TDRStyle->SetFrameBorderMode( 0);

  // Histograms

  TDRStyle->SetHistFillColor(2);
  TDRStyle->SetHistFillStyle(0);
  TDRStyle->SetHistLineColor(1);
  TDRStyle->SetHistLineStyle(0);
  TDRStyle->SetHistLineWidth(2);
  TDRStyle->SetNdivisions(505);

  // Functions

  TDRStyle->SetFuncColor(1);
  TDRStyle->SetFuncStyle(0);
  TDRStyle->SetFuncWidth(2);

  // Various

  TDRStyle->SetMarkerStyle(20);
  TDRStyle->SetMarkerColor(kBlack);
  TDRStyle->SetMarkerSize (1.2);

  TDRStyle->SetTitleSize  (0.055,"X");
  TDRStyle->SetTitleOffset(1.200,"X");
  TDRStyle->SetLabelOffset(0.003,"X");
  TDRStyle->SetLabelSize  (0.050,"X");
  TDRStyle->SetLabelFont  (42   ,"X");

  TDRStyle->SetStripDecimals(kFALSE);

  TDRStyle->SetTitleSize  (0.055,"Y");
  TDRStyle->SetTitleOffset(1.800,"Y");
  TDRStyle->SetLabelOffset(0.008,"Y");
  TDRStyle->SetLabelSize  (0.050,"Y");
  TDRStyle->SetLabelFont  (42   ,"Y");

  TDRStyle->SetTextSize   (0.055);
  TDRStyle->SetTextFont   (42);

  TDRStyle->SetStatFont   (42);
  TDRStyle->SetTitleFont  (42);
  TDRStyle->SetTitleFont  (42,"X");
  TDRStyle->SetTitleFont  (42,"Y");

  TDRStyle->SetOptStat    (0);
  return;
}

void TDRStyle() {
  //char* author   = "\$Author: Ch.Paus $$";
  //char* modified = "\$Modified: Mon Feb  7 14:19:08 2005 by bottom $$";
  //printf(" TDR root style (%s,%s).\n",author,modified);
  //printf("\n");
  //printf(" Use: MakeCanvas(name,title)\n");
  //printf("      InitSubPad(pad,nPad)\n");
  //printf("      InitHist(hist,xTitle,yTitle,color)\n");
  //printf("\n");
  SetStyle();
}

TCanvas* MakeCanvas(const char* name, const char *title)
{
  // Start with a canvas
  TCanvas *canvas = new TCanvas(name,title);
  // General overall stuff
  canvas->SetFillColor      (0);
  canvas->SetBorderMode     (0);
  canvas->SetBorderSize     (10);
  // Set margins to reasonable defaults
  canvas->SetLeftMargin     (0.20);
  canvas->SetRightMargin    (0.05);
  canvas->SetTopMargin      (0.08);
  canvas->SetBottomMargin   (0.15);
  // Setup a frame which makes sense
  canvas->SetFrameFillStyle (0);
  canvas->SetFrameLineStyle (0);
  canvas->SetFrameBorderMode(0);
  canvas->SetFrameBorderSize(10);
  canvas->SetFrameFillStyle (0);
  canvas->SetFrameLineStyle (0);
  canvas->SetFrameBorderMode(0);
  canvas->SetFrameBorderSize(10);

  return canvas;
}

//void InitSubPad(TPad* pad, int i)
//{
//  //printf("Pad: %p, index: %d\n",pad,i);
//
//  pad->cd(i);
//  TPad *tmpPad = pad->GetPad(i);
//  tmpPad->SetLeftMargin  (0.20);
//  tmpPad->SetTopMargin   (0.05);
//  tmpPad->SetRightMargin (0.07);
//  tmpPad->SetBottomMargin(0.15);
//  return;
//}

void InitHist(TH1        *hist,
	      const char *xtit,
	      const char *ytit  = "Number of Entries",
	      EColor      color = kBlack)
{
  hist->SetXTitle(xtit);
  hist->SetYTitle(ytit);
  hist->SetLineColor(color);
  hist->SetTitleSize  (0.055,"Y");
  hist->SetTitleOffset(1.800,"Y");
  hist->SetLabelOffset(0.008,"Y");
  hist->SetLabelSize  (0.050,"Y");
  hist->SetLabelFont  (42   ,"Y");
  hist->SetMarkerStyle(20);
  hist->SetMarkerColor(color);
  hist->SetMarkerSize (0.6);
  // Strangely enough this cannot be set anywhere else??
  hist->GetXaxis()->SetTitleFont(42);
  hist->GetYaxis()->SetTitleFont(42);
  hist->SetTitle("");  
  return;
}

