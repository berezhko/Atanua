Atanua finds plugins through the atanua.xml file.

In order to use the example plugin, copy the .dll 
to the same directory as the atanua.exe. Then 
edit the atanua.xml, adding the following line:

<Plugin dll="plugintest.dll" />

somewhere between the <AtanuaConfig..> and 
</AtanuaConfig> tags.