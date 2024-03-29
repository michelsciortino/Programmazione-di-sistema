// Es1.cpp: definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include "Cacher.h"

using namespace std;

enum coef {
	c_sub = 1,
	c_sum,
	c_div,
	c_mul,
};

cache_t<vector<int>,result> cacher;

result CalcolaSequenza(vector<int> sol);
void combSempl(int pos, vector<int> sol, int k);
result InvalidResult(void);

int main()
{
	vector<int> vet;
	combSempl(0, vet, 7);
	return 0;
}

void combSempl(int pos, vector<int> sol, int k)
{
	if (pos >= k)
	{
		result res = CalcolaSequenza(sol);

		/*if (res.opt != '#') {
		int score = 0;
		printf("\n");
		for (auto it = sol.begin(); it != sol.end(); it++) printf("%d", *it);
		while (res.opt != '=' && res.opt != '#') {
		score += res.score;
		printf("\n\t");

		printf(" %d %c %d score: %d ", res.op1, res.opt, res.op2, score);

		for (auto it = res.next.begin(); it != res.next.end(); it++)
		printf(" %d", *it);
		printf("\n");

		if (cacher.LookUpForSolution(res.next, res) == false) break;
		}
		}*/
		return;
	}
	for (int i = (pos>0) ? sol[pos - 1] : 0; i < 10; i++)
	{
		sol.push_back(i);
		combSempl(pos + 1, sol, k);
		sol.pop_back();
	}
	return;
}

result CalcolaSequenza(vector<int> sol)
{
	if (sol.size() == 1)
	{
		result r;
		bool found = cacher.get(sol, r);
		if (found == true)
			return r;

		if (sol[0] == 0) {
			r.next = vector<int>();
			r.op1 = 0;
			r.op2 = 0;
			r.opt = '=';
			r.score = 0;
		}
		else
		{
			r.next = vector<int>();
			r.op1 = -1;
			r.op2 = -1;
			r.opt = '#';
			r.score = -1;
		}
		return r;
	}

	result res, n_res, best_res;
	best_res = InvalidResult();

	std::sort(sol.begin(), sol.end());
	bool found = cacher.get(sol, res);
	if (found == true)
		return res;

	vector<int> v2;

	for (int i = 0; i < sol.size(); i++)
	{
		if (i > 0 && sol[i] == sol[i - 1]) continue;
		for (int j = i + 1; j < sol.size(); j++)
		{
			if (j>i + 1 && sol[j] == sol[j - 1]) continue;

			v2.clear();
			for (int k = 0; k < sol.size(); k++)
			{
				if (k == i || k == j) continue;
				v2.push_back(sol[k]);
			}

			//somma
			v2.push_back(sol[i] + sol[j]);
			res = CalcolaSequenza(v2);
			if (res.opt != '#')
			{
				n_res.op1 = sol[i];
				n_res.op2 = sol[j];
				n_res.opt = '+';
				n_res.next = v2;
				n_res.score = (sol[i] + sol[j]) * coef::c_sum;
				if (n_res.score > best_res.score)
					best_res = n_res;
			}
			v2.pop_back();

			//sottrazzione
			if (sol[i] - sol[j] >= 0)
			{
				v2.push_back(sol[i] - sol[j]);
				res = CalcolaSequenza(v2);
				if (res.opt != '#')
				{
					n_res.op1 = sol[i];
					n_res.op2 = sol[j];
					n_res.opt = '-';
					n_res.next = v2;
					n_res.score = (sol[i] - sol[j]) * coef::c_sub;
					if (n_res.score > best_res.score)
						best_res = n_res;
				}
				v2.pop_back();
			}

			//moltiplicazione
			if (!(sol[i] == 0 || sol[j] == 0))
			{
				v2.push_back(sol[i] * sol[j]);
				res = CalcolaSequenza(v2);
				if (res.opt != '#')
				{
					n_res.op1 = sol[i];
					n_res.op2 = sol[j];
					n_res.opt = '*';
					n_res.next = v2;
					n_res.score = (sol[i] * sol[j]) * coef::c_mul;
					if (n_res.score > best_res.score)
						best_res = n_res;
				}
				v2.pop_back();
			}

			//divisione
			if ((!(sol[i] == 0 || sol[j] == 0)) && (sol[i] % sol[j]) == 0)
			{
				v2.push_back(sol[i] / sol[j]);
				res = CalcolaSequenza(v2);
				if (res.opt != '#')
				{
					n_res.op1 = sol[i];
					n_res.op2 = sol[j];
					n_res.opt = '*';
					n_res.next = v2;
					n_res.score = (sol[i] / sol[j]) * coef::c_div;
					if (n_res.score > best_res.score)
						best_res = n_res;
				}
			}
		}
	}

	cacher.put(sol, best_res);
	return best_res;
}


result InvalidResult(void)
{
	result res;
	res.op1 = -1;
	res.op2 = -1;
	res.score = -1;
	res.opt = '#';
	return res;
}