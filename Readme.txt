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
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學014 ~ opencv-014-使用resize進行圖像插值[Image Interpolation ~ ​resize()​] 圖像放大/縮小(Zoom In/Zoom Out)
		http://jashliao.eu/wordpress/2020/03/09/fanfuhan-opencv-%e6%95%99%e5%ad%b8014-opencv-014-%e4%bd%bf%e7%94%a8resize%e9%80%b2%e8%a1%8c%e5%9c%96%e5%83%8f%e6%8f%92%e5%80%bc%ef%bc%88image-interpolation%ef%bc%89/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學015 ~ opencv-015-圖像/畫布上繪製幾何形狀及隨機數的生成(繪圖/幾何圖/多邊形/秀英文字/畫線/建立畫布)[line()、ellipse()、circle()、rectangle()、putText()、polylines()]
		http://jashliao.eu/wordpress/2020/03/10/fanfuhan-opencv-%e6%95%99%e5%ad%b8015-opencv-015-%e7%b9%aa%e8%a3%bd%e5%b9%be%e4%bd%95%e5%bd%a2%e7%8b%80%e5%8f%8a%e9%9a%a8%e6%a9%9f%e6%95%b8%e7%9a%84%e7%94%9f%e6%88%90%e7%b9%aa%e5%9c%96-%e5%b9%be/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學016 ~ opencv-016-圖像ROI與ROI操作 [ 簡單使用HSV產生ROI實作 提取 前景&後景 分離 去背/替換背景]
		http://jashliao.eu/wordpress/2020/03/11/fanfuhan-opencv-%e6%95%99%e5%ad%b8016-opencv-016-%e5%9c%96%e5%83%8froi%e8%88%87roi%e6%93%8d%e4%bd%9c%e7%b0%a1%e5%96%ae%e4%bd%bf%e7%94%a8hsv%e7%94%a2%e7%94%9froi%e5%af%a6%e4%bd%9c-%e5%89%8d%e5%be%8c/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學017 ~ opencv-017-計算/顯示 彩色/灰階 對應的直方圖
		http://jashliao.eu/wordpress/2020/03/12/fanfuhan-opencv-%e6%95%99%e5%ad%b8017-opencv-017-%e5%bd%a9%e8%89%b2%e7%9b%b4%e6%96%b9%e5%9c%96/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學018 ~ opencv-018-彩色/灰階 圖像 直方圖均衡化 藉此提高圖像的質量(對比/清晰)
		http://jashliao.eu/wordpress/2020/03/16/fanfuhan-opencv-%e6%95%99%e5%ad%b8018-opencv-018-%e5%9c%96%e5%83%8f%e7%9b%b4%e6%96%b9%e5%9c%96%e5%9d%87%e8%a1%a1%e5%8c%96/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學019 ~ opencv-019-使用HSV圖像進行直方圖比較，進而判斷/計算圖像相似度(相似程度)[以圖找圖/以圖搜圖]
		http://jashliao.eu/wordpress/2020/03/17/fanfuhan-opencv-%e6%95%99%e5%ad%b8019-opencv-019-%e5%9c%96%e5%83%8f%e7%9b%b4%e6%96%b9%e5%9c%96%e6%af%94%e8%bc%83/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學020 ~ opencv-020-使用HSV圖像直方圖透過反向投影(calcBackProjec)計算出特定顏色的不規則ROI的mask [用區域顏色圖片 進行圖像 前景/背景 標記/分割]
		http://jashliao.eu/wordpress/2020/03/19/fanfuhan-opencv-%e6%95%99%e5%ad%b8020-opencv-020-%e5%9c%96%e5%83%8f%e7%9b%b4%e6%96%b9%e5%9c%96%e5%8f%8d%e5%90%91%e6%8a%95%e5%bd%b1-%e7%94%a8%e5%8d%80%e5%9f%9f%e9%a1%8f%e8%89%b2%e5%9c%96%e7%89%87/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學021 ~ opencv-021-圖像捲積和均值模糊(blur)影像濾波器 [打馬賽克/降低銳利度&降低雜訊干擾/顏色分割前置動作]
		http://jashliao.eu/wordpress/2020/03/19/fanfuhan-opencv-%e6%95%99%e5%ad%b8021-opencv-021-%e5%9c%96%e5%83%8f%e6%8d%b2%e7%a9%8d%e5%92%8c%e5%9d%87%e5%80%bc%e6%a8%a1%e7%b3%8a%e5%bd%b1%e5%83%8f%e6%89%93%e9%a6%ac%e8%b3%bd%e5%85%8b/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學022 ~ opencv-022-圖像均值模糊(blur)和高斯模糊(GaussianBlur)影像濾波器實際比較	[保持銳利度&降低雜訊干擾]
		http://jashliao.eu/wordpress/2020/03/19/fanfuhan-opencv-%e6%95%99%e5%ad%b8022-opencv-022-%e5%9c%96%e5%83%8f%e5%9d%87%e5%80%bc%e6%a8%a1%e7%b3%8a%e5%92%8c%e9%ab%98%e6%96%af%e6%a8%a1%e7%b3%8a%e5%bd%b1%e5%83%8f%e6%89%93%e9%a6%ac%e8%b3%bd/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學023 ~ opencv-023-圖像高斯模糊(GaussianBlur)和中值模糊(medianBlur)影像濾波器實際比較 [去除白雜訊]	
		http://jashliao.eu/wordpress/2020/03/19/fanfuhan-opencv-%e6%95%99%e5%ad%b8023-opencv-023-%e5%9c%96%e5%83%8f%e4%b8%ad%e5%80%bc%e6%a8%a1%e7%b3%8a%e4%b8%ad%e5%80%bc%e6%bf%be%e6%b3%a2%e5%bd%b1%e5%83%8f%e5%8e%bb%e9%99%a4%e9%9b%9c%e8%a8%8a/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學024 ~ opencv-024-圖像增加白雜訊&高斯雜訊	[產生濾波器測試輸入圖像]
		http://jashliao.eu/wordpress/2020/03/19/fanfuhan-opencv-%e6%95%99%e5%ad%b8024-opencv-024-%e5%9c%96%e5%83%8f%e5%a2%9e%e5%8a%a0%e9%9b%9c%e8%a8%8a/
			
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學025 ~ opencv-025-圖像去除雜訊	[均值、高斯、中值、非局部平均(速度慢/效果佳) 濾波器]
		http://jashliao.eu/wordpress/2020/03/19/fanfuhan-opencv-%e6%95%99%e5%ad%b8025-opencv-025-%e5%9c%96%e5%83%8f%e5%8e%bb%e9%99%a4%e9%9b%9c%e8%a8%8a/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學026 ~ opencv-026-邊緣保留濾波算法(EPF)–高斯雙邊模糊 [對於 白雜訊/高斯雜訊 無明顯效果]
		http://jashliao.eu/wordpress/2020/03/23/fanfuhan-opencv-%e6%95%99%e5%ad%b8026-opencv-026-%e9%82%8a%e7%b7%a3%e4%bf%9d%e7%95%99%e6%bf%be%e6%b3%a2%e7%ae%97%e6%b3%95epf-%e9%ab%98%e6%96%af%e9%9b%99%e9%82%8a%e6%a8%a1%e7%b3%8a/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學027 ~ opencv-027-邊緣保留濾波算法(EPF)–均值遷移模糊(mean-shift blur)
		http://jashliao.eu/wordpress/2020/03/25/fanfuhan-opencv-%e6%95%99%e5%ad%b8027-opencv-027-%e9%82%8a%e7%b7%a3%e4%bf%9d%e7%95%99%e6%bf%be%e6%b3%a2%e7%ae%97%e6%b3%95epf-%e5%9d%87%e5%80%bc%e9%81%b7%e7%a7%bb%e6%a8%a1%e7%b3%8amean-shi/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學028 ~ opencv-028-圖像積分算法(integral) [應用在3x3 垂直sobel邊緣檢測]
		http://jashliao.eu/wordpress/2020/03/25/fanfuhan-opencv-%e6%95%99%e5%ad%b8028-opencv-028-%e5%9c%96%e5%83%8f%e7%a9%8d%e5%88%86%e5%9c%96%e7%ae%97%e6%b3%95%e6%87%89%e7%94%a8%e5%9c%a8%e9%82%8a%e7%b7%a3%e6%aa%a2%e6%b8%ac/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學029 ~ opencv-029-快速的圖像邊緣保護濾波算法(edgePreservingFilter)[彩色圖像]
		http://jashliao.eu/wordpress/2020/03/25/fanfuhan-opencv-%e6%95%99%e5%ad%b8029-opencv-029-%e5%bf%ab%e9%80%9f%e7%9a%84%e5%9c%96%e5%83%8f%e9%82%8a%e7%b7%a3%e6%bf%be%e6%b3%a2%e7%ae%97%e6%b3%95/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學030 ~ opencv-030-自定義濾波器	(filter2D) [實現 彩色/灰階 圖像 平均模糊、銳化、梯度、Sobel_XY]
		http://jashliao.eu/wordpress/2020/03/25/fanfuhan-opencv-%e6%95%99%e5%ad%b8030-opencv-030-%e8%87%aa%e5%ae%9a%e7%be%a9%e6%bf%be%e6%b3%a2%e5%99%a8/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學031 ~ opencv-031-圖像梯度之Sobel(邊緣檢測) [彩色/灰階 圖像 Sobel運算]
		http://jashliao.eu/wordpress/2020/03/31/fanfuhan-opencv-%e6%95%99%e5%ad%b8031-opencv-031-%e5%9c%96%e5%83%8f%e6%a2%af%e5%ba%a6%e4%b9%8bsobel%e9%82%8a%e7%b7%a3%e6%aa%a2%e6%b8%ac%e5%bd%a9%e8%89%b2sobel%e9%81%8b%e7%ae%97/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學032 ~ opencv-032-圖像梯度之robert算子與prewitt算子與 Sobel比較 (邊緣檢測) [彩色/灰階 圖像 robert & prewitt運算]	
		http://jashliao.eu/wordpress/2020/03/31/fanfuhan-opencv-%e6%95%99%e5%ad%b8032-%e5%9c%96%e5%83%8f%e6%a2%af%e5%ba%a6%e4%b9%8brobert%e7%ae%97%e5%ad%90%e8%88%87prewitt%e7%ae%97%e5%ad%90%e9%82%8a%e7%b7%a3%e6%aa%a2%e6%b8%ac%e5%bd%a9%e8%89%b2/
			
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學033 ~ opencv-033-圖像梯度之拉普拉斯算子(Laplacian)(二階導數算子)[彩色/灰階 圖像 邊緣檢測]	
		http://jashliao.eu/wordpress/2020/03/31/fanfuhan-opencv-%e6%95%99%e5%ad%b8033-opencv-033-%e5%9c%96%e5%83%8f%e6%a2%af%e5%ba%a6%e4%b9%8b%e6%8b%89%e6%99%ae%e6%8b%89%e6%96%af%e7%ae%97%e5%ad%90%e4%ba%8c%e9%9a%8e%e5%b0%8e%e6%95%b8%e7%ae%97/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學034 ~ opencv-034-圖像銳化 ~ 失焦(對焦失敗)的前置動作
		http://jashliao.eu/wordpress/2020/04/01/fanfuhan-opencv-%e6%95%99%e5%ad%b8034-opencv-034-%e5%9c%96%e5%83%8f%e9%8a%b3%e5%8c%96-%e9%82%8a%e7%b7%a3%e6%aa%a2%e6%b8%ac-%e5%a4%b1%e7%84%a6%e5%b0%8d%e7%84%a6%e5%a4%b1%e6%95%97-%e7%9a%84/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學035 ~ opencv-035-圖像銳化增强演算法(USM) ~ 失焦(對焦失敗)的前置動作
		http://jashliao.eu/wordpress/2020/04/08/fanfuhan-opencv-%e6%95%99%e5%ad%b8035-opencv-035-usm-%e5%9c%96%e5%83%8f%e9%8a%b3%e5%8c%96%e5%a2%9e%e5%bc%ba%e6%bc%94%e7%ae%97%e6%b3%95-%e9%82%8a%e7%b7%a3%e6%aa%a2%e6%b8%ac-%e5%a4%b1%e7%84%a6/
	
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學036 ~ opencv-036-Canny邊緣檢測(最推薦的邊緣檢測)
		http://jashliao.eu/wordpress/2020/04/08/fanfuhan-opencv-%e6%95%99%e5%ad%b8036-opencv-036-canny%e9%82%8a%e7%b7%a3%e6%aa%a2%e6%b8%ac/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學037 ~ opencv-037-高斯金字塔圖像(pyrUp / pyrDown)	
		http://jashliao.eu/wordpress/2020/04/08/fanfuhan-opencv-%e6%95%99%e5%ad%b8037-opencv-037-%e5%9c%96%e5%83%8f%e9%87%91%e5%ad%97%e5%a1%94/
	
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學038 ~ opencv-038-拉普拉斯金字塔
		http://jashliao.eu/wordpress/2020/04/09/fanfuhan-opencv-%e6%95%99%e5%ad%b8038-opencv-038-%e6%8b%89%e6%99%ae%e6%8b%89%e6%96%af%e9%87%91%e5%ad%97%e5%a1%94/

	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學039 ~ opencv-039-圖像模板匹配搜尋（matchTemplate） [模板與待測物大小(非待測圖)尺寸必須一致]	
		http://jashliao.eu/wordpress/2020/04/10/fanfuhan-opencv-%e6%95%99%e5%ad%b8039-opencv-039-%e5%9c%96%e5%83%8f%e6%a8%a1%e6%9d%bf%e5%8c%b9%e9%85%8d%e6%90%9c%e5%b0%8b-%e6%a8%a1%e6%9d%bf%e8%88%87%e5%be%85%e6%b8%ac%e7%89%a9%e5%a4%a7%e5%b0%8f/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學040 ~ opencv-040-二值化圖像介紹 (彩色轉灰階+憑感覺手動設定threshold值轉二值化圖)
		http://jashliao.eu/wordpress/2020/04/10/fanfuhan-opencv-%e6%95%99%e5%ad%b8040-opencv-040-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8f%e4%bb%8b%e7%b4%b9-%e5%bd%a9%e8%89%b2%e8%bd%89%e7%81%b0%e9%9a%8e%e6%86%91%e6%84%9f%e8%a6%ba%e6%89%8b/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學041 ~ opencv-041-二值化圖像介紹 (使用threshold函數 製作5種二值化圖，這裡的threshold值還是憑感覺設定)	
		http://jashliao.eu/wordpress/2020/04/10/fanfuhan-opencv-%e6%95%99%e5%ad%b8041-opencv-041-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8f%e4%bb%8b%e7%b4%b9-%e4%bd%bf%e7%94%a8threshold%e5%87%bd%e6%95%b8-%e8%a3%bd%e4%bd%9c5%e7%a8%ae%e4%ba%8c/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學042 ~ opencv-042-二值化圖像OTSU演算法(THRESH_OTSU)	
		http://jashliao.eu/wordpress/2020/04/13/fanfuhan-opencv-%e6%95%99%e5%ad%b8042-opencv-042-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8fotsu%e6%bc%94%e7%ae%97%e6%b3%95thresh_otsu/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學043 ~ opencv-043-二值化圖像TRIANGLE演算法(THRESH_TRIANGLE)		
		http://jashliao.eu/wordpress/2020/04/13/fanfuhan-opencv-%e6%95%99%e5%ad%b8043-opencv-043-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8ftriangle%e6%bc%94%e7%ae%97%e6%b3%95thresh_triangle/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學044 ~ opencv-044-二值化圖像[自適應閥值(adaptiveThreshold)](實作簡易人像素描圖)	
		http://jashliao.eu/wordpress/2020/04/13/fanfuhan-opencv-%e6%95%99%e5%ad%b8044-opencv-044-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8f%e8%87%aa%e9%81%a9%e6%87%89%e9%96%a5%e5%80%bc/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學045 ~ opencv-045-二值化圖像&去除干擾(降噪/去噪/去雜訊) [圖像二值化步驟(SOP)] [抓取 硬幣 輪廓/面積/邊緣 前置動作]	
		http://jashliao.eu/wordpress/2020/04/13/fanfuhan-opencv-%e6%95%99%e5%ad%b8045-opencv-045-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8f%e5%8e%bb%e9%99%a4%e5%b9%b2%e6%93%be%e9%99%8d%e5%99%aa-%e5%8e%bb%e5%99%aa/
	
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學046 ~ opencv-046-二值化圖像 後 連通元件(mask) 標記/尋找/計算(計數)(connectedComponents)[八方鍊碼] [機器視覺: 計算數量步驟(SOP)範例，分類的前置作業]
		http://jashliao.eu/wordpress/2020/04/13/fanfuhan-opencv-%e6%95%99%e5%ad%b8046-opencv-046-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8f%e8%81%af%e9%80%9a%e5%85%83%e4%bb%b6%e6%a8%99%e8%a8%98-%e5%b0%8b%e6%89%be-%e8%a8%88%e7%ae%97%e8%a8%88/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學047 ~ opencv-047-二值化圖像 後 連通元件(mask) 各元件狀態參數統計[八方鍊碼:元件標記/尋找/計算(計數)/參數:中心位置、起始座標、長、寬、面積，取得分類的所需資訊作業][繪製各元件的外矩形]
		http://jashliao.eu/wordpress/2020/04/15/fanfuhan-opencv-%e6%95%99%e5%ad%b8047-opencv-047-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8f%e9%80%a3%e9%80%9a%e7%b5%84%e4%bb%b6%e7%8b%80%e6%85%8b%e7%b5%b1%e8%a8%88%e5%85%ab%e6%96%b9%e9%8d%8a/
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學048 ~ opencv-048-二值化圖像 後 連通元件(mask) 使用抓取輪廓(findContours)函數計算層次(重疊/遠近)參數，取得分類的所需資訊作業 & 使用繪製輪廓(drawContours)函數將結果呈現在畫面上方便觀看與判讀
		http://jashliao.eu/wordpress/2020/04/15/fanfuhan-opencv-%e6%95%99%e5%ad%b8048-opencv-048-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8f%e5%88%86%e6%9e%90%e4%b9%8b%e8%bc%aa%e5%bb%93%e7%99%bc%e7%8f%be/

	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學049 ~ opencv-049-彩色轉二值化圖像(直接使用Canny) 後 連通元件(mask) 使用抓取輪廓(findContours)函數計算層次(重疊/遠近)參數，取得分類的所需資訊作業 & 使用繪製輪廓外接矩形(boundingRect、minAreaRect)函數將結果呈現在畫面上方便觀看與判讀
		http://jashliao.eu/wordpress/2020/04/15/fanfuhan-opencv-%e6%95%99%e5%ad%b8049-opencv-049-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8f%e5%88%86%e6%9e%90%e8%bc%aa%e5%bb%93%e5%a4%96%e6%8e%a5%e7%9f%a9%e5%bd%a2/
		PS.目標物非同類型(顏色)
	
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學050 ~ opencv-050-彩色轉二值化圖像(直接使用Canny) 後 連通元件(mask) 使用抓取輪廓(findContours)函數計算層次(重疊/遠近)參數，取得分類的所需資訊作業 & 計算矩形面積(contourArea)與弧長(arcLengt)[簡易分類過濾]
		http://jashliao.eu/wordpress/2020/04/15/fanfuhan-opencv-%e6%95%99%e5%ad%b8050-opencv-050-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8f%e5%88%86%e6%9e%90%e7%9f%a9%e5%bd%a2%e9%9d%a2%e7%a9%8d%e8%88%87%e5%bc%a7%e9%95%b7/
		PS.目標物為同類型(顏色)
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學051 ~ opencv-051-彩色轉二值化圖像(直接使用Canny) 後 連通元件(mask) 使用抓取輪廓(findContours)函數計算層次(重疊/遠近)參數，取得分類的所需資訊作業 & 使用幾何圖形輪廓逼近(approxPolyDP)[使用形狀進行簡單分類]	
		http://jashliao.eu/wordpress/2020/04/15/fanfuhan-opencv-%e6%95%99%e5%ad%b8051-opencv-051-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8f%e5%88%86%e6%9e%90%e4%bd%bf%e7%94%a8%e5%b9%be%e4%bd%95%e5%9c%96%e5%bd%a2%e8%bc%aa%e5%bb%93%e9%80%bc/
		PS.目標物為同類型(顏色)
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學052 ~ opencv-052-彩色轉二值化圖像(直接使用Canny) 後 連通元件(mask) 使用抓取輪廓(findContours)函數計算層次(重疊/遠近)參數，取得分類的所需資訊作業 & 計算幾何矩與橫縱比
		http://jashliao.eu/wordpress/2020/04/15/fanfuhan-opencv-%e6%95%99%e5%ad%b8052-opencv-052-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8f%e5%88%86%e6%9e%90%ef%bc%88%e4%bd%bf%e7%94%a8%e5%b9%be%e4%bd%95%e7%9f%a9%e8%a8%88%e7%ae%97%e8%bc%aa/
		PS.目標物非同類型(顏色)
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學053 ~ opencv-053-彩色轉二值化圖像(直接使用Canny) 後 連通元件(mask) 使用抓取輪廓(findContours)函數計算層次(重疊/遠近)參數，取得分類的所需資訊作業 & 計算Hu矩(HuMoments)實現 利用數學統計方式進行相似度(相似程度)比對/匹配(matchShapes) [以圖找圖/以圖搜圖] [類似用區域顏色圖片 進行圖像 前景/背景 標記/分割]
		http://jashliao.eu/wordpress/2020/04/15/fanfuhan-opencv-%e6%95%99%e5%ad%b8053-opencv-053-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8f%e5%88%86%e6%9e%90%ef%bc%88%e4%bd%bf%e7%94%a8hu%e7%9f%a9%e5%af%a6%e7%8f%be%e8%bc%aa%e5%bb%93%e5%8c%b9/
		PS.目標物為同類型(顏色) / 統計數學分類形態學

	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學054 ~ opencv-054-彩色轉二值化圖像(直接使用Canny) 後 連通元件(mask) 使用抓取輪廓(findContours)函數計算層次(重疊/遠近)參數，取得分類的所需資訊作業 & 對輪廓找出最適合橢圓(fitEllipse)進行擬合
		http://jashliao.eu/wordpress/2020/04/15/fanfuhan-opencv-%e6%95%99%e5%ad%b8054-opencv-054-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8f%e5%88%86%e6%9e%90%e5%b0%8d%e8%bc%aa%e5%bb%93%e5%9c%93%e8%88%87%e6%a9%a2%e5%9c%93%e6%93%ac%e5%90%88/
		PS.目標物非同類型(顏色)		
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學055 ~ opencv-055-彩色轉二值化圖像(直接使用Canny) 後 連通元件(mask) 使用抓取輪廓(findContours)函數計算層次(重疊/遠近)參數，取得分類的所需資訊作業 & 對輪廓找出最適凸包(convexHull)進行擬合
		http://jashliao.eu/wordpress/2020/04/15/fanfuhan-opencv-%E6%95%99%E5%AD%B8055-opencv-055-%E4%BA%8C%E5%80%BC%E5%8C%96%E5%9C%96%E5%83%8F%E5%88%86%E6%9E%90%E5%87%B8%E5%8C%85%E6%AA%A2%E6%B8%AC/
		PS.目標物為同類型(顏色)
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學056 ~ opencv-056-彩色轉二值化圖像(直接使用Canny) 後 連通元件(mask) 使用抓取輪廓(findContours)函數計算層次(重疊/遠近)參數，取得分類的所需資訊作業 & 對輪廓進行直線擬合(fitLine)
		http://jashliao.eu/wordpress/2020/04/15/fanfuhan-opencv-%e6%95%99%e5%ad%b8056-opencv-056-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8f%e5%88%86%e6%9e%90%e7%9b%b4%e7%b7%9a%e6%93%ac%e5%90%88-%e6%af%94%e5%b0%8d-%e6%90%9c%e5%b0%8b%e8%88%87/
		PS.目標物為同類型(顏色)
	
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學057 ~ opencv-057-彩色轉二值化圖像(直接使用Canny) 後 連通元件(mask) 使用抓取輪廓(findContours)函數計算層次(重疊/遠近)參數，取得分類的所需資訊作業 & 使用輪廓資料判別單一像素相對於一個多邊形屬於內部或外部的分類(pointPolygonTest)
		http://jashliao.eu/wordpress/2020/04/16/fanfuhan-opencv-%e6%95%99%e5%ad%b8057-opencv-057-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8f%e5%88%86%e6%9e%90%e9%bb%9e%e5%a4%9a%e9%82%8a%e5%bd%a2%e6%b8%ac%e8%a9%a6/
		PS.目標物為同類型(顏色)
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學058 ~ opencv-058-彩色轉二值化圖像(直接使用Canny) 後 連通元件(mask) 使用抓取輪廓(findContours)函數計算層次(重疊/遠近)參數，取得分類的所需資訊作業 & 對輪廓進行尋找最大內接圓(minMaxLoc)
		http://jashliao.eu/wordpress/2020/04/16/fanfuhan-opencv-%e6%95%99%e5%ad%b8058-opencv-058-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8f%e5%88%86%e6%9e%90%ef%bc%88%e5%b0%8b%e6%89%be%e6%9c%80%e5%a4%a7%e5%85%a7%e6%8e%a5%e5%9c%93%ef%bc%89/
		PS.目標物為同類型(顏色)	
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學059 ~ opencv-059-彩色轉二值化圖像(直接使用Canny) 後 直接用霍夫直線尋找/偵測/檢測(HoughLines)
		http://jashliao.eu/wordpress/2020/04/16/fanfuhan-opencv-%e6%95%99%e5%ad%b8059-opencv-059-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8f%e5%88%86%e6%9e%90%ef%bc%88%e9%9c%8d%e5%a4%ab%e7%9b%b4%e7%b7%9a%e6%aa%a2%e6%b8%ac%ef%bc%89/
		PS.目標物為同類型(顏色)
	
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學060 ~ opencv-060-彩色轉二值化圖像(直接使用Canny) 後 直接用霍夫直線尋找/偵測/檢測(HoughLinesP) [此方法有更多 限制/過濾 用的設定參數]
		http://jashliao.eu/wordpress/2020/04/16/fanfuhan-opencv-%e6%95%99%e5%ad%b8060-opencv-060-%e4%ba%8c%e5%80%bc%e5%8c%96%e5%9c%96%e5%83%8f%e5%88%86%e6%9e%90%ef%bc%88%e9%9c%8d%e5%a4%ab%e7%9b%b4%e7%b7%9a%e6%aa%a2%e6%b8%ac%e4%ba%8c%ef%bc%89/
		PS.目標物非同類型(顏色)
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學061 ~ opencv-061-彩色轉二值化圖像(直接使用Canny) 後 直接用霍夫圓形尋找/偵測/檢測(HoughCircles) [機器視覺基礎 - 數錢/數硬幣個數]
		http://jashliao.eu/wordpress/2020/04/16/fanfuhan-opencv-%E6%95%99%E5%AD%B8061-opencv-061-%E4%BA%8C%E5%80%BC%E5%8C%96%E5%9C%96%E5%83%8F%E5%88%86%E6%9E%90%EF%BC%88%E9%9C%8D%E5%A4%AB%E5%9C%93%E5%BD%A2%E5%B0%8B%E6%89%BE-%E5%81%B5%E6%B8%AC/
		PS.目標物非同類型(顏色)		
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學062 ~ opencv-062-用圖像形態學 膨脹(dilate) 與 腐蝕(erode) 強化/凸顯 彩色/灰階/黑白 圖像中 連通元件(mask) / 特徵值
		http://jashliao.eu/wordpress/2020/04/16/fanfuhan-opencv-%e6%95%99%e5%ad%b8062-opencv-062-%e5%9c%96%e5%83%8f%e5%bd%a2%e6%85%8b%e5%ad%b8%e8%86%a8%e8%84%b9%e8%88%87%e8%85%90%e8%9d%95/
		PS.目標物非同類型(顏色)	
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學063 ~ opencv-063-彩色轉二值化圖像(直接使用Canny) 後 用圖像形態學 膨脹(dilate) 與 腐蝕(erode) 強化/獲取 連通元件(mask) / 用霍夫圓形尋找/偵測/檢測(HoughCircles) [機器視覺基礎 - 數錢/數硬幣個數]
		http://jashliao.eu/wordpress/2020/04/16/fanfuhan-opencv-%e6%95%99%e5%ad%b8063-opencv-063-%e5%9c%96%e5%83%8f%e5%bd%a2%e6%85%8b%e5%ad%b8%e8%86%a8%e8%84%b9%e8%88%87%e8%85%90%e8%9d%95-%e7%8d%b2%e5%8f%96%e7%b5%90%e6%a7%8b%e5%85%83%e7%b4%a0/
		PS.目標物為同類型(顏色)
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學064 ~ opencv-064-彩色轉二值化圖像(直接使用adaptiveThreshold) 後 用圖像形態學開操作(morphologyEx)去除白色雜訊 強化/獲取 連通元件(mask)
		http://jashliao.eu/wordpress/2020/04/16/fanfuhan-opencv-%e6%95%99%e5%ad%b8064-opencv-064-%e5%9c%96%e5%83%8f%e5%bd%a2%e6%85%8b%e5%ad%b8%e9%96%8b%e6%93%8d%e4%bd%9c/
		PS.目標物和背景一樣[前景/背景相同]
			
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學065 ~ opencv-065-彩色轉二值化圖像(直接使用Canny) 後 用圖像形態學閉操作(morphologyEx)去除黑色雜訊 強化/獲取 連通元件(mask)
		http://jashliao.eu/wordpress/2020/04/16/fanfuhan-opencv-%e6%95%99%e5%ad%b8065-opencv-065-%e5%9c%96%e5%83%8f%e5%bd%a2%e6%85%8b%e5%ad%b8%e9%96%89%e6%93%8d%e4%bd%9c/
		PS.目標物為同類型(顏色)
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學066 ~ opencv-066-彩色轉二值化圖像(直接使用Canny) 後 用圖像形態學開閉操作篩選連通元件(mask)應用演示範例(驗證開閉操作可以互換)
		http://jashliao.eu/wordpress/2020/04/16/fanfuhan-opencv-%e6%95%99%e5%ad%b8066-opencv-066-%e5%9c%96%e5%83%8f%e5%bd%a2%e6%85%8b%e5%ad%b8%e9%96%8b%e9%96%89%e6%93%8d%e4%bd%9c%e6%99%82%e5%80%99%e7%b5%90%e6%a7%8b%e5%85%83%e7%b4%a0%e6%87%89/
		PS.目標物為同類型(顏色)
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學067 ~ opencv-067-彩色轉二值化圖像(直接使用Canny) 後 用圖像形態學頂帽操作(morphologyEx)提取/抓取/尋找/標記 圖像中微小部分
		http://jashliao.eu/wordpress/2020/04/20/fanfuhan-opencv-%e6%95%99%e5%ad%b8067-opencv-067-%e5%9c%96%e5%83%8f%e5%bd%a2%e6%85%8b%e5%ad%b8%e9%a0%82%e5%b8%bd%e6%93%8d%e4%bd%9c-%e6%8f%90%e5%8f%96-%e6%8a%93%e5%8f%96-%e5%b0%8b%e6%89%be/
		PS.目標物為同類型(顏色)
		
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學068 ~ opencv-068-彩色轉二值化圖像(直接使用Canny) 後 用圖像形態學黑帽操作(morphologyEx)提取/抓取/尋找/標記 圖像中小輪廓
		http://jashliao.eu/wordpress/2020/04/20/fanfuhan-opencv-%e6%95%99%e5%ad%b8068-opencv-068-%e5%9c%96%e5%83%8f%e5%bd%a2%e6%85%8b%e5%ad%b8%e9%bb%91%e5%b8%bd%e6%93%8d%e4%bd%9c/
		PS.目標物為同類型(顏色)
	
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學069 ~ opencv-069-彩色轉灰階影圖像後 後 用圖像形態學梯度操作(morphologyEx)提取/抓取/尋找/標記 圖像中輪廓(邊緣)
		http://jashliao.eu/wordpress/2020/04/20/fanfuhan-opencv-%e6%95%99%e5%ad%b8069-opencv-069-%e5%9c%96%e5%83%8f%e5%bd%a2%e6%85%8b%e5%ad%b8%e5%9c%96%e5%83%8f%e6%a2%af%e5%ba%a6/
		PS.目標物非同類型(顏色)	

	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學070 ~ opencv-070-彩色轉二值化圖像(直接使用Canny) 後 用圖像形態學基本梯度操作(morphologyEx)實現OCR文字切割輪廓定位
		http://jashliao.eu/wordpress/2020/04/20/fanfuhan-opencv-%e6%95%99%e5%ad%b8070-opencv-70-%e5%bd%a2%e6%85%8b%e5%ad%b8%e6%87%89%e7%94%a8%e4%bd%bf%e7%94%a8%e5%9f%ba%e6%9c%ac%e6%a2%af%e5%ba%a6%e5%af%a6%e7%8f%be%e8%bc%aa%e5%bb%93%e5%88%86/
		PS.目標物為同類型(顏色)






	
		
		
		
		

	
	jashliao 用 VC++ 實現 fanfuhan OpenCV 教學120 ~ opencv-120-二維碼(QrCode) 檢測 與 解析/識別
		http://jashliao.eu/wordpress/2020/04/29/fanfuhan-opencv-%e6%95%99%e5%ad%b8120-opencv-120-%e4%ba%8c%e7%b6%ad%e7%a2%bc%e6%aa%a2%e6%b8%ac%e8%88%87%e8%ad%98%e5%88%a5/

	OpenCV 常用圖像形態學運算工具 去除雜訊 / 提升連通元件(mask)品質
		http://jashliao.eu/wordpress/2021/10/09/opencv-%e5%b8%b8%e7%94%a8%e5%9c%96%e5%83%8f%e5%bd%a2%e6%85%8b%e5%ad%b8%e9%81%8b%e7%ae%97%e5%b7%a5%e5%85%b7-%e2%80%8b%e5%8e%bb%e9%99%a4%e9%9b%9c%e8%a8%8a-%e6%8f%90%e5%8d%87%e9%80%a3%e9%80%9a%e5%85%83/
		
		
https://github.com/jash-git/jashliao-implements-FANFUHAN-OPENCV-with-VC
		
★前言:
http://jashliao.eu/wordpress/wp-content/uploads/2021/09/20210907031737_66041.jpg
★主題:

★結果圖:

★延伸說明/重點回顧:

		