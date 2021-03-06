void BinCovarianceHggRazor()
{
//=========Macro generated from canvas: c1/c1
//=========  (Thu Mar 16 13:20:44 2017) by ROOT version6.08/00
   TCanvas *c1 = new TCanvas("c1", "c1",624,156,1045,740);
   c1->Range(-2.904762,-4.218216,21.92857,21.55977);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLeftMargin(0.1169703);
   c1->SetRightMargin(0.117929);
   c1->SetBottomMargin(0.1636364);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH2F *corr = new TH2F("corr","Background Covariance Matrix",19,0,19,19,0,19);
   corr->SetBinContent(22,7.200001);
   corr->SetBinContent(23,0.2672915);
   corr->SetBinContent(24,0.001625223);
   corr->SetBinContent(25,3.449828);
   corr->SetBinContent(26,2.003306);
   corr->SetBinContent(27,-0.1299037);
   corr->SetBinContent(28,1.094266);
   corr->SetBinContent(29,0.6026603);
   corr->SetBinContent(30,0.3772124);
   corr->SetBinContent(31,4.398799);
   corr->SetBinContent(32,0.5182461);
   corr->SetBinContent(33,0.4639761);
   corr->SetBinContent(34,-1.045344);
   corr->SetBinContent(35,-0.1582571);
   corr->SetBinContent(36,3.917425);
   corr->SetBinContent(37,0.3293888);
   corr->SetBinContent(38,0.5363065);
   corr->SetBinContent(39,0.112652);
   corr->SetBinContent(40,-0.4577291);
   corr->SetBinContent(43,0.2672915);
   corr->SetBinContent(44,7.06);
   corr->SetBinContent(45,0.02738067);
   corr->SetBinContent(46,10.20474);
   corr->SetBinContent(47,1.258074);
   corr->SetBinContent(48,0.2655874);
   corr->SetBinContent(49,0.05856049);
   corr->SetBinContent(50,0.1689017);
   corr->SetBinContent(51,-0.203687);
   corr->SetBinContent(52,-1.356623);
   corr->SetBinContent(53,-0.1403674);
   corr->SetBinContent(54,0.1150756);
   corr->SetBinContent(55,-1.715165);
   corr->SetBinContent(56,0.3716204);
   corr->SetBinContent(57,1.576942);
   corr->SetBinContent(58,0.4120814);
   corr->SetBinContent(59,-0.5644981);
   corr->SetBinContent(60,2.312829);
   corr->SetBinContent(61,-0.1745173);
   corr->SetBinContent(64,0.001625223);
   corr->SetBinContent(65,0.02738067);
   corr->SetBinContent(66,6.85);
   corr->SetBinContent(67,2.261283);
   corr->SetBinContent(68,1.963802);
   corr->SetBinContent(69,0.0992774);
   corr->SetBinContent(70,0.2134901);
   corr->SetBinContent(71,0.4936861);
   corr->SetBinContent(72,0.09001485);
   corr->SetBinContent(73,3.081846);
   corr->SetBinContent(74,-0.03320625);
   corr->SetBinContent(75,0.02650541);
   corr->SetBinContent(76,0.5989376);
   corr->SetBinContent(77,0.2271089);
   corr->SetBinContent(78,1.603218);
   corr->SetBinContent(79,0.2573114);
   corr->SetBinContent(80,-0.2396841);
   corr->SetBinContent(81,-0.8127553);
   corr->SetBinContent(82,0.8586979);
   corr->SetBinContent(85,3.456811);
   corr->SetBinContent(86,10.22542);
   corr->SetBinContent(87,2.265859);
   corr->SetBinContent(88,1809.14);
   corr->SetBinContent(89,-1.012275);
   corr->SetBinContent(90,6.697715);
   corr->SetBinContent(91,9.605417);
   corr->SetBinContent(92,-0.8592414);
   corr->SetBinContent(93,4.409427);
   corr->SetBinContent(94,54.40217);
   corr->SetBinContent(95,-1.380551);
   corr->SetBinContent(96,1.818917);
   corr->SetBinContent(97,40.60707);
   corr->SetBinContent(98,-3.56902);
   corr->SetBinContent(99,106.0525);
   corr->SetBinContent(100,-2.953686);
   corr->SetBinContent(101,2.048589);
   corr->SetBinContent(102,-36.2908);
   corr->SetBinContent(103,4.93098);
   corr->SetBinContent(106,2.007359);
   corr->SetBinContent(107,1.260622);
   corr->SetBinContent(108,1.967779);
   corr->SetBinContent(109,-1.012275);
   corr->SetBinContent(110,256.49);
   corr->SetBinContent(111,1.281127);
   corr->SetBinContent(112,2.073658);
   corr->SetBinContent(113,2.264486);
   corr->SetBinContent(114,-1.336645);
   corr->SetBinContent(115,38.93255);
   corr->SetBinContent(116,1.86029);
   corr->SetBinContent(117,0.04544767);
   corr->SetBinContent(118,28.44881);
   corr->SetBinContent(119,-2.154541);
   corr->SetBinContent(120,39.41811);
   corr->SetBinContent(121,0.8762429);
   corr->SetBinContent(122,5.192766);
   corr->SetBinContent(123,6.060677);
   corr->SetBinContent(124,2.462171);
   corr->SetBinContent(127,-0.1299037);
   corr->SetBinContent(128,0.2655874);
   corr->SetBinContent(129,0.0992774);
   corr->SetBinContent(130,6.68419);
   corr->SetBinContent(131,1.278538);
   corr->SetBinContent(132,7.25);
   corr->SetBinContent(133,1.210454);
   corr->SetBinContent(134,-0.2097035);
   corr->SetBinContent(135,-8.765232e-05);
   corr->SetBinContent(136,3.902545);
   corr->SetBinContent(137,-0.3170787);
   corr->SetBinContent(138,-0.5794553);
   corr->SetBinContent(139,4.478106);
   corr->SetBinContent(140,-0.4768105);
   corr->SetBinContent(141,1.30636);
   corr->SetBinContent(142,0.3664042);
   corr->SetBinContent(143,-0.3664501);
   corr->SetBinContent(144,1.077817);
   corr->SetBinContent(145,-0.4731456);
   corr->SetBinContent(148,1.073224);
   corr->SetBinContent(149,0.05743426);
   corr->SetBinContent(150,0.2093844);
   corr->SetBinContent(151,9.40167);
   corr->SetBinContent(152,2.029672);
   corr->SetBinContent(153,1.187176);
   corr->SetBinContent(154,24.93);
   corr->SetBinContent(155,0.9106724);
   corr->SetBinContent(156,0.005313865);
   corr->SetBinContent(157,3.027986);
   corr->SetBinContent(158,0.08652855);
   corr->SetBinContent(159,0.1306128);
   corr->SetBinContent(160,5.661592);
   corr->SetBinContent(161,0.4646386);
   corr->SetBinContent(162,-5.217519);
   corr->SetBinContent(163,0.1571939);
   corr->SetBinContent(164,1.094535);
   corr->SetBinContent(165,2.11375);
   corr->SetBinContent(166,0.776071);
   corr->SetBinContent(169,0.6026603);
   corr->SetBinContent(170,0.1689017);
   corr->SetBinContent(171,0.4936861);
   corr->SetBinContent(172,-0.8575042);
   corr->SetBinContent(173,2.259912);
   corr->SetBinContent(174,-0.2097035);
   corr->SetBinContent(175,0.9285287);
   corr->SetBinContent(176,12.01);
   corr->SetBinContent(177,-0.4210026);
   corr->SetBinContent(178,-7.775839);
   corr->SetBinContent(179,-0.4606768);
   corr->SetBinContent(180,0.2147063);
   corr->SetBinContent(181,-1.253046);
   corr->SetBinContent(182,0.3347198);
   corr->SetBinContent(183,1.034227);
   corr->SetBinContent(184,0.01147097);
   corr->SetBinContent(185,0.09434997);
   corr->SetBinContent(186,-0.4641604);
   corr->SetBinContent(187,1.080481);
   corr->SetBinContent(190,0.3772124);
   corr->SetBinContent(191,-0.203687);
   corr->SetBinContent(192,0.09001485);
   corr->SetBinContent(193,4.40052);
   corr->SetBinContent(194,-1.333945);
   corr->SetBinContent(195,-8.765232e-05);
   corr->SetBinContent(196,0.005417521);
   corr->SetBinContent(197,-0.4210026);
   corr->SetBinContent(198,9.769999);
   corr->SetBinContent(199,-6.455331);
   corr->SetBinContent(200,0.05779311);
   corr->SetBinContent(201,-0.1471536);
   corr->SetBinContent(202,-0.3639791);
   corr->SetBinContent(203,-0.06047838);
   corr->SetBinContent(204,-3.252086);
   corr->SetBinContent(205,0.1885649);
   corr->SetBinContent(206,0.6627039);
   corr->SetBinContent(207,0.2928204);
   corr->SetBinContent(208,-1.060261);
   corr->SetBinContent(211,4.407704);
   corr->SetBinContent(212,-1.35937);
   corr->SetBinContent(213,3.088085);
   corr->SetBinContent(214,54.40217);
   corr->SetBinContent(215,38.93255);
   corr->SetBinContent(216,3.910446);
   corr->SetBinContent(217,3.093611);
   corr->SetBinContent(218,-7.791583);
   corr->SetBinContent(219,-6.468398);
   corr->SetBinContent(220,857.89);
   corr->SetBinContent(221,-0.5174752);
   corr->SetBinContent(222,5.507917);
   corr->SetBinContent(223,42.01412);
   corr->SetBinContent(224,4.45688);
   corr->SetBinContent(225,44.79397);
   corr->SetBinContent(226,-4.060115);
   corr->SetBinContent(227,-13.04204);
   corr->SetBinContent(228,-29.73159);
   corr->SetBinContent(229,-2.903305);
   corr->SetBinContent(232,0.5182461);
   corr->SetBinContent(233,-0.1403674);
   corr->SetBinContent(234,-0.03320625);
   corr->SetBinContent(235,-1.377762);
   corr->SetBinContent(236,1.856531);
   corr->SetBinContent(237,-0.3170787);
   corr->SetBinContent(238,0.08822516);
   corr->SetBinContent(239,-0.4606768);
   corr->SetBinContent(240,0.05779311);
   corr->SetBinContent(241,-0.5164298);
   corr->SetBinContent(242,7.650001);
   corr->SetBinContent(243,-0.1925722);
   corr->SetBinContent(244,0.5093402);
   corr->SetBinContent(245,-0.2442501);
   corr->SetBinContent(246,-1.347253);
   corr->SetBinContent(247,0.1364561);
   corr->SetBinContent(248,-0.875925);
   corr->SetBinContent(249,-2.778971);
   corr->SetBinContent(250,-0.1065624);
   corr->SetBinContent(253,0.4639761);
   corr->SetBinContent(254,0.1150756);
   corr->SetBinContent(255,0.02650541);
   corr->SetBinContent(256,1.815242);
   corr->SetBinContent(257,0.04535576);
   corr->SetBinContent(258,-0.5794553);
   corr->SetBinContent(259,0.1331737);
   corr->SetBinContent(260,0.2147063);
   corr->SetBinContent(261,-0.1471536);
   corr->SetBinContent(262,5.496789);
   corr->SetBinContent(263,-0.1925722);
   corr->SetBinContent(264,21.32);
   corr->SetBinContent(265,2.282518);
   corr->SetBinContent(266,2.157221);
   corr->SetBinContent(267,4.829895);
   corr->SetBinContent(268,1.112747);
   corr->SetBinContent(269,0.2784669);
   corr->SetBinContent(270,3.753212);
   corr->SetBinContent(271,1.591138);
   corr->SetBinContent(274,-1.047459);
   corr->SetBinContent(275,-1.718638);
   corr->SetBinContent(276,0.6001508);
   corr->SetBinContent(277,40.60707);
   corr->SetBinContent(278,28.44881);
   corr->SetBinContent(279,4.48717);
   corr->SetBinContent(280,5.784283);
   corr->SetBinContent(281,-1.255583);
   corr->SetBinContent(282,-0.3647164);
   corr->SetBinContent(283,42.01412);
   corr->SetBinContent(284,0.510371);
   corr->SetBinContent(285,2.287134);
   corr->SetBinContent(286,641.45);
   corr->SetBinContent(287,15.21948);
   corr->SetBinContent(288,21.97221);
   corr->SetBinContent(289,-1.498767);
   corr->SetBinContent(290,-0.6768517);
   corr->SetBinContent(291,20.97092);
   corr->SetBinContent(292,-0.8102957);
   corr->SetBinContent(295,-0.1582571);
   corr->SetBinContent(296,0.3716204);
   corr->SetBinContent(297,0.2271089);
   corr->SetBinContent(298,-3.561811);
   corr->SetBinContent(299,-2.150187);
   corr->SetBinContent(300,-0.4768105);
   corr->SetBinContent(301,0.473749);
   corr->SetBinContent(302,0.3347198);
   corr->SetBinContent(303,-0.06047838);
   corr->SetBinContent(304,4.447877);
   corr->SetBinContent(305,-0.2442501);
   corr->SetBinContent(306,2.157221);
   corr->SetBinContent(307,15.18873);
   corr->SetBinContent(308,30.77);
   corr->SetBinContent(309,2.766883);
   corr->SetBinContent(310,-0.04555257);
   corr->SetBinContent(311,-2.424916);
   corr->SetBinContent(312,-3.012514);
   corr->SetBinContent(313,2.505161);
   corr->SetBinContent(316,3.925359);
   corr->SetBinContent(317,1.580133);
   corr->SetBinContent(318,1.606464);
   corr->SetBinContent(319,106.0525);
   corr->SetBinContent(320,39.41811);
   corr->SetBinContent(321,1.309003);
   corr->SetBinContent(322,-5.330599);
   corr->SetBinContent(323,1.036319);
   corr->SetBinContent(324,-3.25867);
   corr->SetBinContent(325,44.79397);
   corr->SetBinContent(326,-1.34998);
   corr->SetBinContent(327,4.839672);
   corr->SetBinContent(328,21.97221);
   corr->SetBinContent(329,2.772484);
   corr->SetBinContent(330,1073.14);
   corr->SetBinContent(331,3.813272);
   corr->SetBinContent(332,-6.864117);
   corr->SetBinContent(333,25.17929);
   corr->SetBinContent(334,8.678784);
   corr->SetBinContent(337,0.3293888);
   corr->SetBinContent(338,0.4120814);
   corr->SetBinContent(339,0.2573114);
   corr->SetBinContent(340,-2.947719);
   corr->SetBinContent(341,0.8744726);
   corr->SetBinContent(342,0.3664042);
   corr->SetBinContent(343,0.1602762);
   corr->SetBinContent(344,0.01147097);
   corr->SetBinContent(345,0.1885649);
   corr->SetBinContent(346,-4.051914);
   corr->SetBinContent(347,0.1364561);
   corr->SetBinContent(348,1.112747);
   corr->SetBinContent(349,-1.495737);
   corr->SetBinContent(350,-0.04555257);
   corr->SetBinContent(351,3.805569);
   corr->SetBinContent(352,9.09);
   corr->SetBinContent(353,0.1903553);
   corr->SetBinContent(354,0.5499064);
   corr->SetBinContent(355,0.5727072);
   corr->SetBinContent(358,0.5373924);
   corr->SetBinContent(359,-0.5656406);
   corr->SetBinContent(360,-0.2401691);
   corr->SetBinContent(361,2.048589);
   corr->SetBinContent(362,5.192766);
   corr->SetBinContent(363,-0.367192);
   corr->SetBinContent(364,1.118255);
   corr->SetBinContent(365,0.09454096);
   corr->SetBinContent(366,0.6640464);
   corr->SetBinContent(367,-13.04204);
   corr->SetBinContent(368,-0.8776976);
   corr->SetBinContent(369,0.27903);
   corr->SetBinContent(370,-0.6768517);
   corr->SetBinContent(371,-2.429823);
   corr->SetBinContent(372,-6.864117);
   corr->SetBinContent(373,0.1907412);
   corr->SetBinContent(374,109.6);
   corr->SetBinContent(375,7.16569);
   corr->SetBinContent(376,-1.180023);
   corr->SetBinContent(379,0.1128808);
   corr->SetBinContent(380,2.31751);
   corr->SetBinContent(381,-0.814401);
   corr->SetBinContent(382,-36.2908);
   corr->SetBinContent(383,6.060677);
   corr->SetBinContent(384,1.079998);
   corr->SetBinContent(385,2.159559);
   corr->SetBinContent(386,-0.4650993);
   corr->SetBinContent(387,0.2934131);
   corr->SetBinContent(388,-29.73159);
   corr->SetBinContent(389,-2.784595);
   corr->SetBinContent(390,3.760808);
   corr->SetBinContent(391,20.97092);
   corr->SetBinContent(392,-3.018612);
   corr->SetBinContent(393,25.17929);
   corr->SetBinContent(394,0.5510197);
   corr->SetBinContent(395,7.16569);
   corr->SetBinContent(396,254.5);
   corr->SetBinContent(397,-1.087226);
   corr->SetBinContent(400,-0.4577291);
   corr->SetBinContent(401,-0.1745173);
   corr->SetBinContent(402,0.8586979);
   corr->SetBinContent(403,4.921021);
   corr->SetBinContent(404,2.457195);
   corr->SetBinContent(405,-0.4731456);
   corr->SetBinContent(406,0.7912881);
   corr->SetBinContent(407,1.080481);
   corr->SetBinContent(408,-1.060261);
   corr->SetBinContent(409,-2.89744);
   corr->SetBinContent(410,-0.1065624);
   corr->SetBinContent(411,1.591138);
   corr->SetBinContent(412,-0.8086588);
   corr->SetBinContent(413,2.505161);
   corr->SetBinContent(414,8.661255);
   corr->SetBinContent(415,0.5727072);
   corr->SetBinContent(416,-1.17764);
   corr->SetBinContent(417,-1.085029);
   corr->SetBinContent(418,30.42);
   corr->SetMinimum(-4000);
   corr->SetMaximum(4000);
   corr->SetEntries(361);
   corr->SetStats(0);
   corr->SetContour(20);
   corr->SetContourLevel(0,-4000);
   corr->SetContourLevel(1,-3600);
   corr->SetContourLevel(2,-3200);
   corr->SetContourLevel(3,-2800);
   corr->SetContourLevel(4,-2400);
   corr->SetContourLevel(5,-2000);
   corr->SetContourLevel(6,-1600);
   corr->SetContourLevel(7,-1200);
   corr->SetContourLevel(8,-800);
   corr->SetContourLevel(9,-400);
   corr->SetContourLevel(10,0);
   corr->SetContourLevel(11,400);
   corr->SetContourLevel(12,800);
   corr->SetContourLevel(13,1200);
   corr->SetContourLevel(14,1600);
   corr->SetContourLevel(15,2000);
   corr->SetContourLevel(16,2400);
   corr->SetContourLevel(17,2800);
   corr->SetContourLevel(18,3200);
   corr->SetContourLevel(19,3600);
   
   TPaletteAxis *palette = new TPaletteAxis(19.11905,-0.7931685,20.2619,19.82922,corr);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#f9f90e");
   palette->SetFillColor(ci);
   palette->SetFillStyle(1001);
   corr->GetListOfFunctions()->Add(palette,"br");

   ci = TColor::GetColor("#000099");
   corr->SetLineColor(ci);
   corr->GetXaxis()->SetBinLabel(1,"Bin 0");
   corr->GetXaxis()->SetBinLabel(2,"Bin 1");
   corr->GetXaxis()->SetBinLabel(3,"Bin 2");
   corr->GetXaxis()->SetBinLabel(4,"Bin 3");
   corr->GetXaxis()->SetBinLabel(5,"Bin 4");
   corr->GetXaxis()->SetBinLabel(6,"Bin 5");
   corr->GetXaxis()->SetBinLabel(7,"Bin 6");
   corr->GetXaxis()->SetBinLabel(8,"Bin 7");
   corr->GetXaxis()->SetBinLabel(9,"Bin 8");
   corr->GetXaxis()->SetBinLabel(10,"Bin 9 HighRes");
   corr->GetXaxis()->SetBinLabel(11,"Bin 10 HighRes");
   corr->GetXaxis()->SetBinLabel(12,"Bin 11 HighRes");
   corr->GetXaxis()->SetBinLabel(13,"Bin 12 HighRes");
   corr->GetXaxis()->SetBinLabel(14,"Bin 13 HighRes");
   corr->GetXaxis()->SetBinLabel(15,"Bin 9 LowRes");
   corr->GetXaxis()->SetBinLabel(16,"Bin 10 LowRes");
   corr->GetXaxis()->SetBinLabel(17,"Bin 11 LowRes");
   corr->GetXaxis()->SetBinLabel(18,"Bin 12 LowRes");
   corr->GetXaxis()->SetBinLabel(19,"Bin 13 LowRes");
   corr->GetXaxis()->SetBit(TAxis::kLabelsVert);
   corr->GetXaxis()->SetLabelFont(42);
   corr->GetXaxis()->SetLabelSize(0.035);
   corr->GetXaxis()->SetTitleSize(0.035);
   corr->GetXaxis()->SetTitleFont(42);
   corr->GetYaxis()->SetBinLabel(1,"Bin 0");
   corr->GetYaxis()->SetBinLabel(2,"Bin 1");
   corr->GetYaxis()->SetBinLabel(3,"Bin 2");
   corr->GetYaxis()->SetBinLabel(4,"Bin 3");
   corr->GetYaxis()->SetBinLabel(5,"Bin 4");
   corr->GetYaxis()->SetBinLabel(6,"Bin 5");
   corr->GetYaxis()->SetBinLabel(7,"Bin 6");
   corr->GetYaxis()->SetBinLabel(8,"Bin 7");
   corr->GetYaxis()->SetBinLabel(9,"Bin 8");
   corr->GetYaxis()->SetBinLabel(10,"Bin 9 HighRes");
   corr->GetYaxis()->SetBinLabel(11,"Bin 10 HighRes");
   corr->GetYaxis()->SetBinLabel(12,"Bin 11 HighRes");
   corr->GetYaxis()->SetBinLabel(13,"Bin 12 HighRes");
   corr->GetYaxis()->SetBinLabel(14,"Bin 13 HighRes");
   corr->GetYaxis()->SetBinLabel(15,"Bin 9 LowRes");
   corr->GetYaxis()->SetBinLabel(16,"Bin 10 LowRes");
   corr->GetYaxis()->SetBinLabel(17,"Bin 11 LowRes");
   corr->GetYaxis()->SetBinLabel(18,"Bin 12 LowRes");
   corr->GetYaxis()->SetBinLabel(19,"Bin 13 LowRes");
   corr->GetYaxis()->SetLabelFont(42);
   corr->GetYaxis()->SetLabelSize(0.035);
   corr->GetYaxis()->SetTitleSize(0.035);
   corr->GetYaxis()->SetTitleFont(42);
   corr->GetZaxis()->SetLabelFont(42);
   corr->GetZaxis()->SetLabelSize(0.035);
   corr->GetZaxis()->SetTitleSize(0.035);
   corr->GetZaxis()->SetTitleFont(42);
   corr->Draw("colz+text");
   
   TPaveText *pt = new TPaveText(0.2371347,0.9343684,0.7628653,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *AText = pt->AddText("Background Covariance Matrix");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
