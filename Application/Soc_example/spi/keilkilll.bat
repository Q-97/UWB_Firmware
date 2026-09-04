del *.bak /s
del *.ddk /s
del *.edk /s
del *.lst /s
del *.lnp /s
del *.mpf /s
del *.mpj /s
del *.obj /s
del *.omf /s
::del *.opt /s  ::不允许删除JLINK的设置
del *.plg /s
del *.rpt /s
del *.tmp /s
del *.__i /s
del *.crf /s
del *.o /s
del *.d /s
del *.axf /s
del *.tra /s
del *.dep /s   
del *.i /s  
rd /q /s MDK-ARM\Bin
rd /q /s MDK-ARM\Listings  
rd /q /s MDK-ARM\Objects  
rd /q /s MDK-ARM\RTE
del soc_sdk.uvguix.*/s   
del JLinkLog.txt /s
del *.iex /s
del *.htm /s
del *.map /s
exit
