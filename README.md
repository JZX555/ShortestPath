# 前言
今天将给大家介绍的是图论算法中的另外一个基础部分——最短路径算法；其中又分为无权最短路径，单源最短路径，具有负边的最短路径以及无圈图等；而这次将介绍常见的两个——无权最短路径以及单源最短路径。接下来就开始我们的讲解吧~~  

# 原理
最短路径算法，顾名思义是一种用来找出从某地到另外某个地方所经过的路径长度最短的算法，如图一所示。
![](http://img.blog.csdn.net/20180311153220189?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvd2VpeGluXzQxNDI3NDAw/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)  
上图中所展示的正是`Dijkstra算法`查找后的结果，我们可以清楚的了解从`v1`点开始，到其他点的最短路径该如何选择，以及其所经过的没条边的权重；接下来我将具体介绍其实现方式：

## 无权最短路径：
在无权图中因为边上不存在权重，因此我们可以把每条边的权重都当做1。当我们从某个顶点开始检索的时候，我们将该节点**压入一个队列中或者是栈中（当然你也可以通过for循环来检索，不过时间复杂度会上升到`O(n * n) `）**，然后将该节点标位已知节点，接下来检索所有与该节点相连接的节点，更新他们的路径与距离，并标位已知，接下来重复刚才的步骤，只不过__我们只对未更新过的节点（即距离无穷的节点）进行操作__，直到所有节点都已知。  
以下是伪代码：  

	int Unweighted(vertex start) {  
	    queue Q;  
	    vertex v, w;  
	  
	    enqueue(start);  
	    // 遍历所有的节点  
	    while(all vertex is retrieved) {  
	        v = dequeue;  
	        v is known;  
	  
	        // 遍历相邻节点  
	        for each w adjacent to v  
	            // 更新路径  
	            if Dist to w is infinity {  
	                Dist to w = Dist to v + 1;  
	                Path to w is v;  
	                enqueue(w);  
	            }  
	    }  
	} 
伪代码中有几点需要说明：  
1.遍历所有节点我们只需要保证当队列是空时即可，这和拓扑排序很相似，大家可以想一想；  
2.更新路径时我们只需要保证路径未被更新过即可进行更新，因为只要我们**更新过得路径即为最短路径**，关于这一点大家也可以想一想；  

## Dijkstra算法：  
在赋权图中情况看似变得很复杂了，但其实我们用和无权图中相似的思想，也可以解决它，这就是我接下来介绍的`Dijkstra算法`；同上面类似，我们也从某个顶点开始检索将其标位已知，并更新其链接的顶点的路径信息，不同之处是，我们**选择未知节点中路径距离最短的作为下一次检索的起始顶点**，然后一直进行检索直到所有顶点都已知；  
以下是伪代码：  

	int Dijkstra(vertex start) {  
	    vertex v, w;  
	  
	    // 遍历所有的节点  
	    while(true) {  
	        v = smallest unknown distance vertex;  
	        if v = novertex  
	            break;  
	  
	        v is known;  
	        // 遍历相邻节点  
	        for each w adjacent to v  
	            // 更新路径  
	            if(w is unknown && Dist to v + v->w < Dist to w) {  
	                Dist to w = Dist ti v + v->w;  
	                Path to w is v;  
	            }  
	    }  
	} 
当然上诉代码中也有几点需要注意的地方：  
1.查找最短距离未知节点的方法会直接影响到我们的时间复杂度，**最好的方法是使用优先队列来完成**；当然使用不同优先队列也会有差距，其中我们按照时间复杂度来排序的话：斐波拉契堆`(O(E + V * logV))` < 配对堆`(O(E * logV))` < 二叉堆`(O(E * logV + V * logV))`；  
2.查找最短距离未知节，并以此节点开始检索也是算法中最重要的东西，他**保证了我们每次更新的起始节点v的距离一定是最短的**，从而保证了算法的正确性；  

最后，最短路径的讨论我们到这里就结束啦，如果有什么问题欢迎大家一起讨论啊~~  
CSDN博客地址：[JZX555的CSDN](http://blog.csdn.net/weixin_41427400/article/details/79516355)  
参考文献：《数据结构与算法分析——C语言描述》