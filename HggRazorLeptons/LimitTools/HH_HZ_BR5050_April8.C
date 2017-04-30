void NarrowResLimit_BIAS_fix()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Apr 17 21:41:00 2017) by ROOT version6.08/00
   TCanvas *c = new TCanvas("c", "c",0,0,800,700);
   c->SetHighLightColor(2);
   c->Range(70.62313,-2.962963,424.0304,21.7284);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetLeftMargin(0.12);
   c->SetRightMargin(0.05);
   c->SetTopMargin(0.07);
   c->SetBottomMargin(0.12);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1[72] = {
   127,
   150,
   175,
   200,
   225,
   250,
   275,
   300,
   325,
   350,
   375,
   400,
   425,
   450,
   475,
   500,
   525,
   550,
   575,
   600,
   625,
   650,
   675,
   700,
   725,
   750,
   775,
   800,
   825,
   850,
   875,
   900,
   925,
   950,
   975,
   1000,
   1000,
   975,
   950,
   925,
   900,
   875,
   850,
   825,
   800,
   775,
   750,
   725,
   700,
   675,
   650,
   625,
   600,
   575,
   550,
   525,
   500,
   475,
   450,
   425,
   400,
   375,
   350,
   325,
   300,
   275,
   250,
   225,
   200,
   175,
   150,
   127};
   Double_t Graph0_fy1[72] = {
   4.394166,
   3.269014,
   2.281077,
   1.795562,
   1.500096,
   1.287736,
   1.161428,
   1.055228,
   0.9757494,
   0.8926331,
   0.8247213,
   0.7715081,
   0.7305585,
   0.6672511,
   0.6449805,
   0.6057736,
   0.517143,
   0.5489402,
   0.4292996,
   0.4113562,
   0.4861389,
   0.3830725,
   0.4578354,
   0.4423489,
   0.4293396,
   0.1695467,
   0.4106964,
   0.4051763,
   0.3966511,
   0.3894269,
   0.3884539,
   0.3771823,
   0.3091944,
   0.03235322,
   0.3040975,
   0.03739135,
   0.1650232,
   1.334804,
   0.1281593,
   1.349753,
   1.621526,
   1.669983,
   1.667727,
   1.689203,
   1.73217,
   1.742218,
   0.7096741,
   1.811204,
   1.862112,
   1.912201,
   1.625035,
   2.018743,
   1.735116,
   1.796926,
   2.244026,
   2.13116,
   2.456158,
   2.589756,
   2.669067,
   2.897864,
   3.049249,
   3.227219,
   3.489144,
   3.794959,
   4.038285,
   4.477998,
   4.96499,
   5.762184,
   6.87571,
   8.817389,
   12.97842,
   16.88073};
   TGraph *graph = new TGraph(72,Graph0_fx1,Graph0_fy1);
   graph->SetName("Graph0");
   graph->SetTitle("");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ffcc00");
   graph->SetFillColor(ci);

   ci = TColor::GetColor("#ffcc00");
   graph->SetLineColor(ci);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","",100,39.7,1087.3);
   Graph_Graph1->SetMinimum(0);
   Graph_Graph1->SetMaximum(20);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1->SetLineColor(ci);
   Graph_Graph1->GetXaxis()->SetTitle("Higgsino mass m_{#tilde{#chi}^{0}_{1}} [GeV]");
   Graph_Graph1->GetXaxis()->SetRange(8,35);
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetLabelOffset(0.003);
   Graph_Graph1->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph1->GetXaxis()->SetTitleOffset(0.95);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetTitle("#sigma^{95%}_{excl} [pb]");
   Graph_Graph1->GetYaxis()->CenterTitle(true);
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleSize(0.05);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph1);
   
   graph->Draw("afc");
   
   Double_t Graph1_fx2[72] = {
   127,
   150,
   175,
   200,
   225,
   250,
   275,
   300,
   325,
   350,
   375,
   400,
   425,
   450,
   475,
   500,
   525,
   550,
   575,
   600,
   625,
   650,
   675,
   700,
   725,
   750,
   775,
   800,
   825,
   850,
   875,
   900,
   925,
   950,
   975,
   1000,
   1000,
   975,
   950,
   925,
   900,
   875,
   850,
   825,
   800,
   775,
   750,
   725,
   700,
   675,
   650,
   625,
   600,
   575,
   550,
   525,
   500,
   475,
   450,
   425,
   400,
   375,
   350,
   325,
   300,
   275,
   250,
   225,
   200,
   175,
   150,
   127};
   Double_t Graph1_fy2[72] = {
   5.937705,
   4.405603,
   3.082351,
   2.414984,
   2.017591,
   1.735463,
   1.56524,
   1.416416,
   1.321998,
   1.207884,
   1.111465,
   1.058026,
   0.9885693,
   0.9029036,
   0.8745563,
   0.8230866,
   0.7026609,
   0.7418046,
   0.5841189,
   0.5604716,
   0.6596301,
   0.5219352,
   0.6212258,
   0.6002125,
   0.5857862,
   0.2306907,
   0.5595726,
   0.5551435,
   0.5393168,
   0.5309686,
   0.5292673,
   0.5139098,
   0.4230415,
   0.04308531,
   0.416068,
   0.05086922,
   0.1116076,
   0.9076857,
   0.08897489,
   0.9228991,
   1.111195,
   1.144402,
   1.142856,
   1.164057,
   1.193667,
   1.203457,
   0.4930128,
   1.25516,
   1.286275,
   1.324147,
   1.122511,
   1.406006,
   1.20539,
   1.24833,
   1.567047,
   1.484302,
   1.719886,
   1.824264,
   1.880133,
   2.047264,
   2.173901,
   2.293826,
   2.4877,
   2.713886,
   2.897111,
   3.212566,
   3.561939,
   4.133855,
   4.948077,
   6.34444,
   9.142198,
   12.22165};
   graph = new TGraph(72,Graph1_fx2,Graph1_fy2);
   graph->SetName("Graph1");
   graph->SetTitle("Graph");

   ci = TColor::GetColor("#00cc00");
   graph->SetFillColor(ci);

   ci = TColor::GetColor("#00cc00");
   graph->SetLineColor(ci);
   
   TH1F *Graph_Graph2 = new TH1F("Graph_Graph2","Graph",100,39.7,1087.3);
   Graph_Graph2->SetMinimum(0);
   Graph_Graph2->SetMaximum(13.43951);
   Graph_Graph2->SetDirectory(0);
   Graph_Graph2->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph2->SetLineColor(ci);
   Graph_Graph2->GetXaxis()->SetLabelFont(42);
   Graph_Graph2->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph2->GetXaxis()->SetTitleFont(42);
   Graph_Graph2->GetYaxis()->SetLabelFont(42);
   Graph_Graph2->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph2->GetYaxis()->SetTitleFont(42);
   Graph_Graph2->GetZaxis()->SetLabelFont(42);
   Graph_Graph2->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph2->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph2);
   
   graph->Draw("fc");
   
   Double_t Graph2_fx3[36] = {
   127,
   150,
   175,
   200,
   225,
   250,
   275,
   300,
   325,
   350,
   375,
   400,
   425,
   450,
   475,
   500,
   525,
   550,
   575,
   600,
   625,
   650,
   675,
   700,
   725,
   750,
   775,
   800,
   825,
   850,
   875,
   900,
   925,
   950,
   975,
   1000};
   Double_t Graph2_fy3[36] = {
   8.426267,
   6.268671,
   4.374201,
   3.430326,
   2.865855,
   2.469366,
   2.227158,
   2.008464,
   1.8711,
   1.724635,
   1.581488,
   1.490612,
   1.411494,
   1.289179,
   1.250871,
   1.179301,
   1.006757,
   1.068659,
   0.842151,
   0.813183,
   0.9536519,
   0.7572708,
   0.8981293,
   0.8677496,
   0.8422295,
   0.3325973,
   0.8118786,
   0.8009662,
   0.7810977,
   0.7668715,
   0.7679089,
   0.7456269,
   0.6159825,
   0.0606771,
   0.6058285,
   0.07449171};
   graph = new TGraph(36,Graph2_fx3,Graph2_fy3);
   graph->SetName("Graph2");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   graph->SetLineStyle(2);
   graph->SetLineWidth(3);
   
   TH1F *Graph_Graph3 = new TH1F("Graph_Graph3","Graph",100,39.7,1087.3);
   Graph_Graph3->SetMinimum(0);
   Graph_Graph3->SetMaximum(9.262826);
   Graph_Graph3->SetDirectory(0);
   Graph_Graph3->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3->SetLineColor(ci);
   Graph_Graph3->GetXaxis()->SetLabelFont(42);
   Graph_Graph3->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph3->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph3->GetXaxis()->SetTitleFont(42);
   Graph_Graph3->GetYaxis()->SetLabelFont(42);
   Graph_Graph3->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph3->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph3->GetYaxis()->SetTitleFont(42);
   Graph_Graph3->GetZaxis()->SetLabelFont(42);
   Graph_Graph3->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph3->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph3->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph3);
   
   graph->Draw("pc");
   
   Double_t Graph3_fx4[36] = {
   127,
   150,
   175,
   200,
   225,
   250,
   275,
   300,
   325,
   350,
   375,
   400,
   425,
   450,
   475,
   500,
   525,
   550,
   575,
   600,
   625,
   650,
   675,
   700,
   725,
   750,
   775,
   800,
   825,
   850,
   875,
   900,
   925,
   950,
   975,
   1000};
   Double_t Graph3_fy4[36] = {
   8.015504,
   6.26485,
   4.027197,
   2.983891,
   2.440333,
   2.10048,
   1.874747,
   1.742912,
   1.709486,
   1.582234,
   1.493523,
   1.440137,
   1.416639,
   1.310931,
   1.312091,
   1.260924,
   1.099444,
   1.197841,
   0.9454077,
   0.9194098,
   1.144506,
   0.880317,
   1.10372,
   1.09278,
   1.06871,
   0.6578577,
   1.044374,
   1.038463,
   1.007557,
   1.004638,
   0.994984,
   0.9690483,
   0.7786225,
   0.03669083,
   0.7624395,
   0.1487541};
   graph = new TGraph(36,Graph3_fx4,Graph3_fy4);
   graph->SetName("Graph3");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(20);
   graph->SetMarkerSize(0.5);
   
   TH1F *Graph_Graph4 = new TH1F("Graph_Graph4","Graph",100,39.7,1087.3);
   Graph_Graph4->SetMinimum(0);
   Graph_Graph4->SetMaximum(8.813385);
   Graph_Graph4->SetDirectory(0);
   Graph_Graph4->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph4->SetLineColor(ci);
   Graph_Graph4->GetXaxis()->SetLabelFont(42);
   Graph_Graph4->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph4->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph4->GetXaxis()->SetTitleFont(42);
   Graph_Graph4->GetYaxis()->SetLabelFont(42);
   Graph_Graph4->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph4->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph4->GetYaxis()->SetTitleFont(42);
   Graph_Graph4->GetZaxis()->SetLabelFont(42);
   Graph_Graph4->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph4->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph4->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph4);
   
   graph->Draw("c");
   
   Double_t Graph4_fx5[36] = {
   127,
   150,
   175,
   200,
   225,
   250,
   275,
   300,
   325,
   350,
   375,
   400,
   425,
   450,
   475,
   500,
   525,
   550,
   575,
   600,
   625,
   650,
   675,
   700,
   725,
   750,
   775,
   800,
   825,
   850,
   875,
   900,
   925,
   950,
   975,
   1000};
   Double_t Graph4_fy5[36] = {
   7.6022,
   3.83231,
   2.26794,
   1.33561,
   0.860597,
   0.577313,
   0.400107,
   0.284857,
   0.20736,
   0.153835,
   0.116006,
   0.0887434,
   0.0686963,
   0.0537508,
   0.0424699,
   0.0338454,
   0.0271867,
   0.0219917,
   0.0179062,
   0.0146602,
   0.012062,
   0.00997229,
   0.00828246,
   0.00690746,
   0.00578355,
   0.00485987,
   0.00409781,
   0.00343578,
   0.0029337,
   0.00250407,
   0.00213679,
   0.00182277,
   0.00155453,
   0.00132537,
   0.00112975,
   0.000972953};
   graph = new TGraph(36,Graph4_fx5,Graph4_fy5);
   graph->SetName("Graph4");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineWidth(3);
   
   TH1F *Graph_Graph5 = new TH1F("Graph_Graph5","Graph",100,39.7,1087.3);
   Graph_Graph5->SetMinimum(0);
   Graph_Graph5->SetMaximum(8.362323);
   Graph_Graph5->SetDirectory(0);
   Graph_Graph5->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph5->SetLineColor(ci);
   Graph_Graph5->GetXaxis()->SetLabelFont(42);
   Graph_Graph5->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph5->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph5->GetXaxis()->SetTitleFont(42);
   Graph_Graph5->GetYaxis()->SetLabelFont(42);
   Graph_Graph5->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph5->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph5->GetYaxis()->SetTitleFont(42);
   Graph_Graph5->GetZaxis()->SetLabelFont(42);
   Graph_Graph5->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph5->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph5->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph5);
   
   graph->Draw("pc");
   
   Double_t Graph5_fx6[36] = {
   127,
   150,
   175,
   200,
   225,
   250,
   275,
   300,
   325,
   350,
   375,
   400,
   425,
   450,
   475,
   500,
   525,
   550,
   575,
   600,
   625,
   650,
   675,
   700,
   725,
   750,
   775,
   800,
   825,
   850,
   875,
   900,
   925,
   950,
   975,
   1000};
   Double_t Graph5_fy6[36] = {
   7.901666,
   3.990861,
   2.368407,
   1.398972,
   0.9039897,
   0.6080689,
   0.4225223,
   0.3015794,
   0.2200826,
   0.163695,
   0.1237659,
   0.09493142,
   0.07366668,
   0.05777929,
   0.04576194,
   0.03655505,
   0.02943178,
   0.02386278,
   0.01947408,
   0.01598346,
   0.01317121,
   0.01090759,
   0.009075453,
   0.007583104,
   0.006361856,
   0.005356895,
   0.004526631,
   0.003800836,
   0.003251576,
   0.002780703,
   0.002377469,
   0.002032015,
   0.001736331,
   0.00148322,
   0.001266726,
   0.001088602};
   graph = new TGraph(36,Graph5_fx6,Graph5_fy6);
   graph->SetName("Graph5");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineStyle(2);
   graph->SetLineWidth(3);
   
   TH1F *Graph_Graph6 = new TH1F("Graph_Graph6","Graph",100,39.7,1087.3);
   Graph_Graph6->SetMinimum(0);
   Graph_Graph6->SetMaximum(8.691724);
   Graph_Graph6->SetDirectory(0);
   Graph_Graph6->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph6->SetLineColor(ci);
   Graph_Graph6->GetXaxis()->SetLabelFont(42);
   Graph_Graph6->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph6->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph6->GetXaxis()->SetTitleFont(42);
   Graph_Graph6->GetYaxis()->SetLabelFont(42);
   Graph_Graph6->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph6->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph6->GetYaxis()->SetTitleFont(42);
   Graph_Graph6->GetZaxis()->SetLabelFont(42);
   Graph_Graph6->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph6->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph6->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph6);
   
   graph->Draw("pc");
   
   Double_t Graph6_fx7[36] = {
   127,
   150,
   175,
   200,
   225,
   250,
   275,
   300,
   325,
   350,
   375,
   400,
   425,
   450,
   475,
   500,
   525,
   550,
   575,
   600,
   625,
   650,
   675,
   700,
   725,
   750,
   775,
   800,
   825,
   850,
   875,
   900,
   925,
   950,
   975,
   1000};
   Double_t Graph6_fy7[36] = {
   7.302734,
   3.673759,
   2.167473,
   1.272248,
   0.8172043,
   0.5465571,
   0.3776917,
   0.2681346,
   0.1946374,
   0.143975,
   0.1082461,
   0.08255538,
   0.06372591,
   0.04972231,
   0.03917786,
   0.03113575,
   0.02494162,
   0.02012062,
   0.01633832,
   0.01333694,
   0.01095279,
   0.00903699,
   0.007489468,
   0.006231816,
   0.005205244,
   0.004362845,
   0.003668989,
   0.003070724,
   0.002615824,
   0.002227437,
   0.001896111,
   0.001613525,
   0.001372729,
   0.00116752,
   0.000992774,
   0.000857304};
   graph = new TGraph(36,Graph6_fx7,Graph6_fy7);
   graph->SetName("Graph6");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineStyle(2);
   graph->SetLineWidth(3);
   
   TH1F *Graph_Graph7 = new TH1F("Graph_Graph7","Graph",100,39.7,1087.3);
   Graph_Graph7->SetMinimum(0);
   Graph_Graph7->SetMaximum(8.032922);
   Graph_Graph7->SetDirectory(0);
   Graph_Graph7->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph7->SetLineColor(ci);
   Graph_Graph7->GetXaxis()->SetLabelFont(42);
   Graph_Graph7->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph7->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph7->GetXaxis()->SetTitleFont(42);
   Graph_Graph7->GetYaxis()->SetLabelFont(42);
   Graph_Graph7->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph7->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph7->GetYaxis()->SetTitleFont(42);
   Graph_Graph7->GetZaxis()->SetLabelFont(42);
   Graph_Graph7->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph7->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph7->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph7);
   
   graph->Draw("pc");
   
   TLegend *leg = new TLegend(0.51,0.63,0.89,0.7,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph4"," NLO+NNL theory #pm s.d.","l");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(3);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.51,0.32,0.89,0.57,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("Graph3"," Observed","l");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(3);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph2"," Expected","l");
   entry->SetLineColor(1);
   entry->SetLineStyle(2);
   entry->SetLineWidth(3);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph1"," 68% expected","f");

   ci = TColor::GetColor("#00cc00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#00cc00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph0"," 95% expected","f");

   ci = TColor::GetColor("#ffcc00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ffcc00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   TLatex *   tex = new TLatex(0.81,0.58,"95% CL upper limits");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(41);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.29,0.88,"pp #rightarrow #tilde{#chi}^{0,#pm}_{i} #tilde{#chi}^{0,#pm}_{j} #rightarrow  #tilde{#chi}^{0}_{1} #tilde{#chi}^{0}_{1} + X_{soft}; #tilde{#chi}^{0}_{1} #rightarrow H #tilde{G} (50%)");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.038);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.705,0.81,"#tilde{#chi}^{0}_{1} #rightarrow Z #tilde{G} (50%)");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.038);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.54,0.75,"m_{#tilde{#chi}^{0}_{2}} #approx m_{#tilde{#chi}^{#pm}_{1}} #approx m_{#tilde{#chi}^{0}_{1}};  m_{#tilde{G}} = 1 GeV");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.038);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.955,0.945,"35.9 fb^{-1} (13 TeV)");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.25,0.94,"CMS");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(61);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
