# GLdiagram
用法：
singlediagram *diagramptr＝new singlediagram(x,y,w,h);
於座標x,y建立一張寬度w,長度h的圖表

	diagramptr->setvaluerange(0,200);
	圖表的值的顯示範圍(y軸),最小為0,最大為200
	diagramptr->setdatacolor(color3f(RED));
	將代表資料的線條設為紅色
	diagramptr->setaxiscolor(color3f(WHITE));
	將x軸,y軸設為白色
	diagramptr->setdisplayscope(60);
	將x軸能顯示的料數目設為60
	diagramptr->settitle("mydiagram");
	將圖表名稱設為"mydiagram" (ASCII only)
	
diagrams.push_back(diagramptr);
將diagramptr加入繪圖排程

diagramptr->addvalue(i);
再圖表上新增值i並畫出
