//#include "ShotestPath.h"
//
//
//#include "Queue.h"
//
//
//ShotestPath::ShotestPath()
//{
//}
//
//
//ShotestPath::~ShotestPath()
//{
//}
//
//
//
//Vector2 ShotestPath::findShortest(int m[19][25], Vector2 source, Vector2 dest)
//{
//	
//		Queue<Vector2> shortest;
//		Queue<Vector2> path;
//		path.enQueue(source);
//
//		Vector2 current = source;
//
//		m[current.x][current.y] = 0;
//
//
//		while (!path.isEmpty())  // this loop is main part its purpose is to label postions to destination
//		{
//			current = path.deQueue();
//
//
//			if (current.x + 1 < 19 && m[current.x + 1][current.y] == 0)   // check down
//			{
//				path.enQueue(Vector2(current.x + 1, current.y));
//				m[current.x + 1][current.y] = m[current.x][current.y] + 1;
//
//				if (current.x == dest.x && current.y == dest.y)
//				{
//					break;
//				}
//
//			}
//			if (current.y - 1 >= 0 && m[current.x][current.y - 1] == 0)   // check left
//			{
//				path.enQueue(Vector2(current.x, current.y - 1));
//				m[current.x][current.y - 1] = m[current.x][current.y] + 1;
//
//				if (current.x == dest.x && current.y == dest.y)
//				{
//					break;
//				}
//
//			}
//			if (current.x - 1 >= 0 && m[current.x - 1][current.y] == 0)			// check up
//			{
//				path.enQueue(Vector2(current.x - 1, current.y));
//				m[current.x - 1][current.y] = m[current.x][current.y] + 1;
//
//				if (current.x == dest.x && current.y == dest.y)
//				{
//					break;
//				}
//
//			}
//			if (current.y + 1 < 19 && m[current.x][current.y + 1] == 0)		// check right
//			{
//				path.enQueue(Vector2(current.x, current.y + 1));
//				m[current.x][current.y + 1] = m[current.x][current.y] + 1;
//
//				if (current.x == dest.x && current.y == dest.y)
//				{
//					break;
//				}
//
//			}
//
//		}
//
//		m[source.x][source.y] = 0;
//
//
//		for (int i = 0; i < 6; i++)
//		{
//			for (int j = 0; j < 6; j++)
//			{
//				cout << m[i][j] << "      ";
//			}
//			cout << endl;
//		}
//
//		while (!path.isEmpty())             // this loop find shortest path  // move backward from destination to source 
//		{
//			if (m[current.x][current.y] == 0)
//			{
//				return shortest.GetFirstPair();
//			}
//
//			if (current.x + 1 < 6 && (m[current.x + 1][current.y] == m[current.x][current.y] - 1)) // to find shortest enqueue the position when previous postion is less than current by 1
//			{
//				shortest.enQueue(Vector2(current.x + 1, current.y));
//				current.x = current.x + 1;
//		
//			}
//
//			if (current.y - 1 >= 0 && (m[current.x][current.y - 1] == m[current.x][current.y] - 1))
//			{
//				shortest.enQueue(Vector2(current.x, current.y - 1));
//				current.y = current.y - 1;
//		
//
//			}
//			if (current.x - 1 >= 0 && (m[current.x - 1][current.y] == m[current.x][current.y] - 1))
//			{
//				shortest.enQueue(Vector2(current.x - 1, current.y));
//				current.x = current.x - 1;
//		
//
//			}
//			if (current.y + 1 < 6 && (m[current.x][current.y + 1] == m[current.x][current.y] - 1))
//			{
//				shortest.enQueue(Vector2(current.x, current.y + 1));
//				current.y = current.y + 1;
//		
//
//			}
//
//		}
//
//	
//}