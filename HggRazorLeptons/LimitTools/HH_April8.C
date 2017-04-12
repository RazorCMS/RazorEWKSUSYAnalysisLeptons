void NarrowResLimit_BIAS_fix()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Apr 10 10:53:36 2017) by ROOT version6.08/00
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
   4.492912,
   2.989351,
   1.853736,
   1.367153,
   1.091291,
   0.9330486,
   0.8191125,
   0.7456437,
   0.6864038,
   0.6243913,
   0.5862077,
   0.5420936,
   0.5236133,
   0.47164,
   0.4516509,
   0.4256239,
   0.404768,
   0.393613,
   0.3294625,
   0.363154,
   0.3423726,
   0.3304295,
   0.3232556,
   0.3137911,
   0.1267252,
   0.1369608,
   0.1154844,
   0.0968271,
   0.08267749,
   0.01391173,
   0.03108511,
   0.02651688,
   0.02261464,
   0.01928092,
   0.02634819,
   0,
   0,
   0.09371263,
   0.01928092,
   0.02261464,
   0.02651688,
   0.03108511,
   0.05947047,
   0.08267749,
   0.0968271,
   0.1154844,
   0.1369608,
   0.4879431,
   1.303452,
   1.353055,
   1.38158,
   1.419458,
   1.508035,
   1.368127,
   1.612711,
   1.648772,
   1.716672,
   1.810913,
   1.89106,
   2.081995,
   2.129243,
   2.302515,
   2.43756,
   2.669614,
   2.900014,
   3.158167,
   3.575274,
   4.181445,
   5.224817,
   7.191648,
   11.97667,
   16.12501};
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
   6.014014,
   4.039628,
   2.498253,
   1.842492,
   1.470717,
   1.252416,
   1.103906,
   1.010239,
   0.9250565,
   0.8431887,
   0.7916248,
   0.7281358,
   0.7085373,
   0.6399259,
   0.6111602,
   0.5759411,
   0.5499731,
   0.5348164,
   0.4470396,
   0.4954832,
   0.4661581,
   0.449593,
   0.4410463,
   0.4298409,
   0.1696288,
   0.1369608,
   0.1154844,
   0.0968271,
   0.08267749,
   0.01887649,
   0.03108511,
   0.02651688,
   0.02261464,
   0.01928092,
   0.03577568,
   0,
   0,
   0.0698204,
   0.01928092,
   0.02261464,
   0.02651688,
   0.03108511,
   0.04088806,
   0.08267749,
   0.0968271,
   0.1154844,
   0.1369608,
   0.3447188,
   0.905512,
   0.9399718,
   0.9582487,
   0.9917611,
   1.05031,
   0.9528682,
   1.129747,
   1.161764,
   1.205848,
   1.279587,
   1.336218,
   1.4754,
   1.513412,
   1.636569,
   1.74317,
   1.909119,
   2.073885,
   2.265704,
   2.568748,
   3.018563,
   3.76071,
   5.127523,
   8.487235,
   11.88577};
   graph = new TGraph(72,Graph1_fx2,Graph1_fy2);
   graph->SetName("Graph1");
   graph->SetTitle("Graph");

   ci = TColor::GetColor("#00cc00");
   graph->SetFillColor(ci);

   ci = TColor::GetColor("#00cc00");
   graph->SetLineColor(ci);
   
   TH1F *Graph_Graph2 = new TH1F("Graph_Graph2","Graph",100,39.7,1087.3);
   Graph_Graph2->SetMinimum(0);
   Graph_Graph2->SetMaximum(13.07435);
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
   5.819572,
   3.55473,
   2.621656,
   2.092663,
   1.775914,
   1.570733,
   1.429849,
   1.31625,
   1.201836,
   1.12834,
   1.043428,
   1.01166,
   0.911244,
   0.8726237,
   0.8223374,
   0.7879895,
   0.7662733,
   0.6463019,
   0.7123941,
   0.669064,
   0.6481988,
   0.6341259,
   0.6108785,
   0.2376678,
   0.1369608,
   0.1154844,
   0.0968271,
   0.08267749,
   0.02729045,
   0.03108511,
   0.02651688,
   0.02261464,
   0.01928092,
   0.04977961,
   0};
   graph = new TGraph(36,Graph2_fx3,Graph2_fy3);
   graph->SetName("Graph2");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   graph->SetLineStyle(2);
   graph->SetLineWidth(3);
   
   TH1F *Graph_Graph3 = new TH1F("Graph_Graph3","Graph",100,39.7,1087.3);
   Graph_Graph3->SetMinimum(0);
   Graph_Graph3->SetMaximum(9.268893);
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
   10.27331,
   7.404134,
   3.772582,
   2.446697,
   1.875086,
   1.553406,
   1.370861,
   1.254832,
   1.203943,
   1.124415,
   1.077004,
   1.02256,
   1.036354,
   0.9460945,
   0.9296192,
   0.8832381,
   0.8763759,
   0.870122,
   0.728539,
   0.8510751,
   0.8226659,
   0.7910548,
   0.7899912,
   0.7705235,
   0.1629919,
   0.1369608,
   0.1154844,
   0.0968271,
   0.08267749,
   0.03642814,
   0.03108511,
   0.02651688,
   0.02261464,
   0.01928092,
   0.06995783,
   0};
   graph = new TGraph(36,Graph3_fx4,Graph3_fy4);
   graph->SetName("Graph3");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(20);
   graph->SetMarkerSize(0.5);
   
   TH1F *Graph_Graph4 = new TH1F("Graph_Graph4","Graph",100,39.7,1087.3);
   Graph_Graph4->SetMinimum(0);
   Graph_Graph4->SetMaximum(11.30064);
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
      tex = new TLatex(0.29,0.88,"pp #rightarrow #tilde{#chi}^{0,#pm}_{i} #tilde{#chi}^{0,#pm}_{j} #rightarrow  #tilde{#chi}^{0}_{1} #tilde{#chi}^{0}_{1} + X_{soft}; #tilde{#chi}^{0}_{1} #rightarrow H #tilde{G} (100%)");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.038);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.553,0.81,"m_{#tilde{#chi}^{0}_{2}} #approx m_{#tilde{#chi}^{#pm}_{1}} #approx m_{#tilde{#chi}^{0}_{1}};  m_{#tilde{G}} = 1 GeV");
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
