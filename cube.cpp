#include <cstdio>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

struct Cube
{
	int data[8];
	int lastStep;
	int dist;
};

class CubeSolver
{
private:
	int gap[7];
public:
	int hashlist[8 * 7 * 6 * 5 * 4 * 3 * 2 * 1];


	CubeSolver()
	{
		memset(hashlist, -1, sizeof(hashlist));

		gap[0] = 1;
		for (int i = 1; i < 7; i++)
		{
			gap[i] = gap[i - 1] * (i + 1);
		}

		CubeSolver::genHashList();
	}

	Cube flip(Cube c)
	{
		int temp[4] = { c.data[0], c.data[1], c.data[2], c.data[3] };
		for (int i = 0; i < 4; i++)
		{
			c.data[i] = c.data[7 - i];
		}
		for (int i = 0; i < 4; i++)
		{
			c.data[i + 4] = temp[3 - i];
		}

		c.lastStep = 0;

		c.dist++;

		return c;
	}

	Cube rotate(Cube c)
	{
		int temp = c.data[1];
		c.data[1] = c.data[2];
		c.data[2] = c.data[5];
		c.data[5] = c.data[6];
		c.data[6] = temp;

		if (c.lastStep > 0)
		{
			c.lastStep++;
		}
		else
		{
			c.lastStep = 1;
		}

		c.dist++;

		return c;
	}

	Cube translate(Cube c)
	{
		int temp = c.data[0];
		c.data[0] = c.data[1];
		c.data[1] = c.data[2];
		c.data[2] = c.data[3];
		c.data[3] = temp;
		temp = c.data[7];
		c.data[7] = c.data[6];
		c.data[6] = c.data[5];
		c.data[5] = c.data[4];
		c.data[4] = temp;

		if (c.lastStep < 0)
		{
			c.lastStep--;
		}
		else
		{
			c.lastStep = -1;
		}

		c.dist++;

		return c;
	}

	int genHash(Cube cube)
	{
		int h = 0;
		for (int i = 0; i < 7; i++)
		{
			h += (cube.data[i] - 1) * gap[6 - i];
			for (int j = i+1; j < 8; j++)
			{
				if (cube.data[j] > cube.data[i])
				{
					cube.data[j]--;
				}
			}
		}
		return h;
	}

	void genHashList()
	{
		Cube start;
		for (int i = 0; i < 8; i++)
		{
			start.data[i] = i + 1;
		}
		start.lastStep = 0;
		start.dist = 0;
		hashlist[genHash(start)] = start.dist;

		vector<Cube> queue;

		Cube temp;
		int h;

		temp = flip(start);
		temp.lastStep = 0;
		queue.emplace_back(temp);
		h = genHash(temp);
		hashlist[h] = temp.dist;

		temp = rotate(start);
		temp.lastStep = 1;
		queue.emplace_back(temp);
		h = genHash(temp);
		hashlist[h] = temp.dist;

		temp = translate(start);
		temp.lastStep = -1;
		queue.emplace_back(temp);
		h = genHash(temp);
		hashlist[h] = temp.dist;


		
		while (!queue.empty())
		{
			// ·­×ª
			if (queue[0].lastStep != 0)
			{
				temp = flip(queue[0]);
				h = genHash(temp);
				if (hashlist[h] == -1)
				{
					hashlist[h] = temp.dist;
					queue.emplace_back(temp);
				}
			}

			// Ğı×ª
			if (queue[0].lastStep != 3)
			{
				temp = rotate(queue[0]);
				h = genHash(temp);
				if (hashlist[h] == -1)
				{
					hashlist[h] = temp.dist;
					queue.emplace_back(temp);
				}
			}

			// Æ½ÒÆ
			if (queue[0].lastStep != -3)
			{
				temp = translate(queue[0]);
				h = genHash(temp);
				if (hashlist[h] == -1)
				{
					hashlist[h] = temp.dist;
					queue.emplace_back(temp);
				}
			}

			queue.erase(queue.begin());
		}

		
		return;
	}
};






int main()
{
	CubeSolver c;

	Cube t;

	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			cin >> t.data[j];
		}
		cout << c.hashlist[c.genHash(t)] << endl;
	}
	
	return 0;
}