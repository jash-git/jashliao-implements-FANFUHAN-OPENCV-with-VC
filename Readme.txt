jashliao 用 VC++ 實現 FANFUHAN OPENCV教學範例

資料來源: https://fanfuhan.github.io/


自己對應部落格網址列表:
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學001 ~ opencv-001-讀取（imread）、顯示（imshow）與儲存(imwrite)圖像
		http://jashliao.eu/wordpress/2020/02/07/fanfuhan-opencv-%e6%95%99%e5%ad%b8001-opencv-001-%e8%ae%80%e5%8f%96%ef%bc%88imread%ef%bc%89%e8%88%87%e9%a1%af%e7%a4%ba%ef%bc%88imshow%ef%bc%89%e5%9c%96%e5%83%8f/

	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學002 ~ opencv-002-色彩空間轉換（cvtcolor）與圖像保存（imwrite）
		http://jashliao.eu/wordpress/2020/02/07/fanfuhan-opencv-%e6%95%99%e5%ad%b8002-opencv-002-%e8%89%b2%e5%bd%a9%e7%a9%ba%e9%96%93%e8%bd%89%e6%8f%9b%ef%bc%88cvtcolor%ef%bc%89%e8%88%87%e5%9c%96%e5%83%8f%e4%bf%9d%e5%ad%98%ef%bc%88imwrite/
	
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學003 ~ opencv-003-圖像對象（Mat）創建與賦值 [圖片拷貝(複製)、建立空白畫布、建立運算濾波器(Filter)]
		http://jashliao.eu/wordpress/2020/02/10/fanfuhan-opencv-%e6%95%99%e5%ad%b8003-opencv-003-%e5%9c%96%e5%83%8f%e5%b0%8d%e8%b1%a1%ef%bc%88mat%ef%bc%89%e5%89%b5%e5%bb%ba%e8%88%87%e8%b3%a6%e5%80%bc/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學004 ~ opencv-004-圖像像素讀寫操作	[一般像素存取操作(Vec3b)/指標像素存取操作(uchar *)、手工RGB顏色分離、圖片顏色反轉]
		http://jashliao.eu/wordpress/2020/02/11/fanfuhan-opencv-%e6%95%99%e5%ad%b8004-opencv-004-%e5%9c%96%e5%83%8f%e5%83%8f%e7%b4%a0%e8%ae%80%e5%af%ab%e6%93%8d%e4%bd%9c/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學005 ~ opencv-005-像素(pixel)計算操作 [圖片合成/融合 (加/減/乘/除) ]	
		http://jashliao.eu/wordpress/2020/02/13/fanfuhan-opencv-%e6%95%99%e5%ad%b8005-opencv-005-%e5%83%8f%e7%b4%a0pixel%e8%a8%88%e7%ae%97%e6%93%8d%e4%bd%9c-%e5%9c%96%e7%89%87%e5%90%88%e6%88%90/

	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學006 ~ opencv-006-Look Up Table(LUT)查找表的使用 [顏色轉換(偽顏色)/手寫灰階轉二值化]	
		http://jashliao.eu/wordpress/2020/02/14/fanfuhan-opencv-%e6%95%99%e5%ad%b8006-opencv-006-look-up-tablelut%e6%9f%a5%e6%89%be%e8%a1%a8%e7%9a%84%e4%bd%bf%e7%94%a8-%e9%a1%8f%e8%89%b2%e8%bd%89%e6%8f%9b/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學007 ~ opencv-007-圖像像素之邏輯(AND、OR、XOR、NOT)運算操作 [使用顏色特性，圖片預先處理，藉此凸顯/過濾特徵點]
		http://jashliao.eu/wordpress/2020/02/17/fanfuhan-opencv-%e6%95%99%e5%ad%b8007-opencv-007-%e5%9c%96%e5%83%8f%e5%83%8f%e7%b4%a0%e4%b9%8b%e9%82%8f%e8%bc%af%e6%93%8d%e4%bd%9c-%e4%bd%bf%e7%94%a8%e9%a1%8f%e8%89%b2%e7%89%b9%e6%80%a7%ef%bc%8c/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學008 ~ opencv-008-圖像顏色通道(RGB)的分離(拆分)與合併(組合) [過濾特定顏色干擾訊號]	
		http://jashliao.eu/wordpress/2020/02/20/fanfuhan-opencv-%e6%95%99%e5%ad%b8008-opencv-008-%e5%9c%96%e5%83%8f%e9%80%9a%e9%81%93%e7%9a%84%e5%88%86%e9%9b%a2%e8%88%87%e5%90%88%e4%bd%b5/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學009 ~ opencv-009-色彩空間(HSV)提取圖像的前景和背景及其應用	
		http://jashliao.eu/wordpress/2020/02/21/fanfuhan-opencv-%e6%95%99%e5%ad%b8009-opencv-009-%e8%89%b2%e5%bd%a9%e7%a9%ba%e9%96%93%e5%8f%8a%e5%85%b6%e6%87%89%e7%94%a8%ef%bc%88%e6%8f%90%e5%8f%96%e5%9c%96%e5%83%8f%e7%9a%84%e5%89%8d%e6%99%af/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學010 ~ opencv-010-圖像像素值統計函數[minMaxLoc(一維陣列<灰階>最大最小值&位置座標) / meanStdDev(計算每一顏色通道平均值&標準差) / 普通圖像轉化為二值化圖像 / 彩色圖的相似顏色都標成相同區域，簡易分割圖片方式]
		http://jashliao.eu/wordpress/2020/02/24/fanfuhan-opencv-%e6%95%99%e5%ad%b8010-opencv-010-%e5%9c%96%e5%83%8f%e5%83%8f%e7%b4%a0%e5%80%bc%e7%b5%b1%e8%a8%88%e5%8f%8a%e6%87%89%e7%94%a8%ef%bc%88%e6%99%ae%e9%80%9a%e5%9c%96%e5%83%8f%e8%bd%89/

	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學011 ~ opencv-011-圖像(像素)資料預先處理[ 歸一化 normalize()]
		http://jashliao.eu/wordpress/2020/03/04/fanfuhan-opencv-%e6%95%99%e5%ad%b8011-opencv-011-%e5%9c%96%e5%83%8f%e5%83%8f%e7%b4%a0%e6%ad%b8%e4%b8%80%e5%8c%96/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學012 ~ opencv-012-視頻讀寫[抓取影片資訊、影片撥放拷貝(讀取影格/顯示圖像(畫面)&寫入檔案)]	
		http://jashliao.eu/wordpress/2020/03/06/fanfuhan-opencv-%e6%95%99%e5%ad%b8012-opencv%e7%9a%84-012%e8%a6%96%e9%a0%bb%e8%ae%80%e5%af%ab%e6%8a%93%e5%8f%96%e5%bd%b1%e7%89%87%e7%95%ab%e9%9d%a2%e5%a4%a7%e5%b0%8f%e3%80%81%e5%bd%b1%e7%89%87/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學013 ~ opencv-013-圖片XY翻轉[flip()-(顛倒/轉向/旋轉)]	
		http://jashliao.eu/wordpress/2020/03/06/fanfuhan-opencv-%e6%95%99%e5%ad%b8013-opencv%e7%9a%84-013%e5%9c%96%e7%89%87%e7%bf%bb%e8%bd%89%e9%a1%9b%e5%80%92-%e8%bd%89%e5%90%91-%e6%97%8b%e8%bd%89/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學014 ~ opencv-014-使用resize進行圖像插值（resize() ~ Image Interpolation）圖像放大/縮小(Zoom In/Zoom Out)
		http://jashliao.eu/wordpress/2020/03/09/fanfuhan-opencv-%e6%95%99%e5%ad%b8014-opencv-014-%e4%bd%bf%e7%94%a8resize%e9%80%b2%e8%a1%8c%e5%9c%96%e5%83%8f%e6%8f%92%e5%80%bc%ef%bc%88image-interpolation%ef%bc%89/
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
https://github.com/jash-git/jashliao-implements-FANFUHAN-OPENCV-with-VC
		
★前言:
http://jashliao.eu/wordpress/wp-content/uploads/2021/09/20210907031737_66041.jpg
★主題:

★結果圖:

★延伸說明/重點回顧:

		