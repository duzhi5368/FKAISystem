@echo off
echo ============================
echo 正在删除BIN目录下垃圾文件，请梢等……
echo ============================
del *tds *#00 *.aps *.plg *.bsc *.hpj *.clw *.exp *.cbp *.mdp *.ilk *.sbr *.res *.obj *.pch *.pdb *.ncb *.idb *.tmp *.opt mt.dep *.manifest BuildLog.htm *.suo Thumbs.db /f/s/q/a
echo ============================
echo ========已经删除完毕========
echo ============================
echo. & pause