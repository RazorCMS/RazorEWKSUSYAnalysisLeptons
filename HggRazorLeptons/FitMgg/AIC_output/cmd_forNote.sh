rm aic_tables.tex aic_plots.tex
cat FitChoices_Table_highpt_ColorTable_WithStatus.tex FitChoices_Table_highres_ColorTable_WithStatus.tex FitChoices_Table_lowres_ColorTable_WithStatus.tex FitChoices_Table_hzbb_ColorTable_WithStatus.tex >> aic_tables.tex
cat FitChoices_Plot_highpt.tex FitChoices_Plot_highres.tex FitChoices_Plot_lowres.tex FitChoices_Plot_hzbb.tex >> aic_plots.tex
sed -i "s/_0\./_0d/g" `grep _0\. -rl aic_plots.tex`
python renamePDF.py highpt
python renamePDF.py highres
python renamePDF.py lowres
python renamePDF.py hzbb
rm -rf /afs/cern.ch/user/z/zhicaiz/private/CMS_AN/tdr2/notes/AN-16-129/trunk/figs/*/*.pdf
cp -r highpt /afs/cern.ch/user/z/zhicaiz/private/CMS_AN/tdr2/notes/AN-16-129/trunk/figs/
cp -r highres /afs/cern.ch/user/z/zhicaiz/private/CMS_AN/tdr2/notes/AN-16-129/trunk/figs/
cp -r lowres /afs/cern.ch/user/z/zhicaiz/private/CMS_AN/tdr2/notes/AN-16-129/trunk/figs/
cp -r hzbb /afs/cern.ch/user/z/zhicaiz/private/CMS_AN/tdr2/notes/AN-16-129/trunk/figs/
rm /afs/cern.ch/user/z/zhicaiz/private/CMS_AN/tdr2/notes/AN-16-129/trunk/figs/*/*.root
cp aic_tables.tex /afs/cern.ch/user/z/zhicaiz/private/CMS_AN/tdr2/notes/AN-16-129/trunk/
