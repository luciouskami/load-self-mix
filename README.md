# load-self-mix
一个war3加载模型包和音效包的例子  
1.物编中设置通用文件夹路径 :yourmapname/xxxx.mdx。  
2.新建一个mpq文件，按照路径添加文件（模型，贴图，音效），注意要与物编中设置的路径完全一致。  
3.二进制合并两个文件，执行批处理文件：copy /b LoadSelfMix.dll + FateSoundPack.mpq FateSoundPack.mixtape （名字自己改）。  
4.放到魔兽目录下。  
