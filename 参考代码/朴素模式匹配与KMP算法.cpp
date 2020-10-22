#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 朴素模式匹配算法
const char *strstr(const char *src, const char *pattern, int &count)
{
	const char *p0 = src;
	const char *p1 = pattern;
	while (*p0 != '\0' && *p1 != '\0')
	{
		count++;
		if (*p0 == *p1)
		{
			p0++;
			p1++;
		}
		else
		{
			p0 -= (p1 - pattern) - 1;
			p1 = pattern;
		}
	}
	if (*p1 == '\0')
		return p0 - (p1 - pattern);
	else
		return nullptr;
}

// KMP模式匹配算法——在nextval向量指导下的模式匹配
const char *strstr(const char *src, const char *pattern, vector<int> &nextval, int &count)
{
	const char *p0 = src;
	const char *p1 = pattern;
	while (*p0 != '\0' && *p1 != '\0')
	{
		count++;
		if (*p0 == *p1)
		{
			p0++;
			p1++;
		}
		else
		{
			int i = p1 - pattern;
			if (nextval[i] == -1)
			{
				p0++;
				p1 = pattern;
			}
			else
				p1 = pattern + nextval[i];
		}
	}
	if (*p1 == '\0')
		return p0 - (p1 - pattern);
	else
		return nullptr;
}

// KMP算法之nextval向量计算算法
// 计算指定模式串pattern的nextval向量
int GetNextval(vector<int> &nextval, const char *pattern)
{
	// k的初始值为K[0]，因K[1]的值为0，所以初始化K[0]为-1，这样k++刚好可以得到K[1]
	int k = -1;
	nextval[0] = -1;
	for (int i = 1; pattern[i] != '\0'; i++)
	{
		// 此时k为K[i-1]，即pattern[0~i-2]的最大相同首尾真子串的长度
		while (k != -1 && pattern[k] != pattern[i - 1])
			k = nextval[k];
		
		// 此时k+1为K[i]，即pattern[0~i-1]的最大相同首尾真子串的长度
		k++;

		if (pattern[k] != pattern[i])
			nextval[i] = k;
		else
			nextval[i] = nextval[k];
	}
	return 0;
}


int main()
{
	char *text = "Conrad and Sally Walden live in the city of Anville with their single mother Joan Walden, who works for Hank Humberfloob of Humberfloob Real Estate, Hank Humberfloob warns Joan the day the movie takes place that she will be fired if her house is messy for the upcoming meet and greet party (because of his germaphobia). Later that day, Conrad trashes the house, causing their dog Nevins to run down the street in fright. Joan punishes Conrad for a week while re-cleaning the house. Their next-door neighbor, Lawrence Quinn, whom Joan is dating to Conrad's dismay, brings back Nevins, and Sally is grateful. When Lawrence leaves, Joan is called back to the office again, leaving the kids with Mrs. Kwan, a lethargic babysitter, and making sure they are not allowed to enter the living room, which is being kept pristine for the upcoming party. Lawrence is constantly on the lookout for any mischief that Conrad is up to, as he wants nothing more than to send him away to military school for the rest of his life, earning Conrad the reputation of \"troublemaker\", while his sister is characterized as \"perfect and well - behaved\".Once their mother leaves, and Mrs. Kwan is falling asleep, Sally and Conrad discover a humanoid, oversized talking Cat in their house. The Cat wants them to learn how to have fun, though the children's pet Fish doesn't want the Cat around while Joan is away. In a series of antics, the Cat balances some stuff, ruins Joan's best dress, jumps on the living room's couch, and bakes cupcakes that explode. In the process, he even releases two troublemaking Things from a crate that he explains is actually a portal from their world to his.The Cat tells Conrad that he only has one rule: to never open the crate. The Cat tells the Things to fix Joan's dress; however, they end up wrecking the house instead, since they only do the opposite of what is said. Despite the Cat's warning, Conrad picks the lock anyway. When the crate's lock attaches itself to the collar of the family dog, Nevins, which then escapes, the Cat and the kids go out to find it.Meanwhile, Lawrence is revealed to be a disgusting and unemployed slob who has false teeth and is in financial ruin, showing off the impression as a successful businessman in the hopes of marrying Joan for her fortune and sponging off of her. Lawrence sees Nevins running across the street and sees that this is an opportunity for Joan to send Conrad to military school as punishment and allow him to move in. They are almost discovered by some children from the nearby birthday party of Sally's former friend, Denise, during which the Cat hides by pretending to be a pinata and is subsequently beaten.While spying on Nevins, the Cat and the kids see Lawrence arrive and take the dog. The Cat and the kids are witness to this and, using the Cat's super-powered car, they follow Lawrence into town but end up crashing the car to a pole. Lawrence goes to see Joan, but the Cat (disguised as a hippie) intervenes and tricks Lawrence into handing over the dog and he and the kids escape. They later see an anxious Lawrence driving home with Joan, but Conrad uses Things 1 and 2 to stall her by posing as police officers, giving them time to get back using Lawrence's car. While distracting them, Lawrence sees the group drive past and races back to the house, telling Joan to meet him there.During this time, \"the mother of all messes\" has been emitted from the unlocked crate and enters the house. Lawrence catches the kids out the front and pushes them into the house, where they find it surprisingly immaculate. A hidden Cat then reveals himself to Lawrence, who stumbles back in fear sneezing (he is allergic to cats), tearing through a wall and falling off a bottomless cliff, revealing the Cat's world. The trio navigate their way through the oversized house by riding Mrs. Kwan and find the crate sucking up things that disappear forever once gone through.Sally is nearly sucked up, but Conrad manages to put the lock back on the crate to save her and the house. The house returns to its normal proportions but immediately falls apart. The Cat then tells the kids that he had planned the whole day, including making not opening the crate his only rule (as he knew Conrad could not resist), and also admits he never really lost his magic hat.The kids angrily tell the Cat to leave the house and think about all the trouble and for the destruction he has caused, and then brace themselves for their mother's arrival. However, the Cat happily returns to clean up his mess with a great cleaning contraption, much to Conrad and Sally's surprise and delight.Afterwards, when everything is restored to its original cleanliness, the Cat says goodbye to Conrad and Sally, and they plead with him not to go, but he departs just as Joan is coming in. Lawrence arrives, thinking he has busted the kids, but when Joan sees the clean house (and a messy Lawrence), she doesn't believe him, and dumps him as a result. He cries and sneezes in his hands, much to Joan's disgust (as it is possible that she has learned of his sloppiness). He asks her to marry him, but she closes the door, and Sally locks him out of the house. Conrad and Sally jump for joy, as Mrs. Kwan falls asleep again.When her party is successful, Joan and her kids play in the living room by jumping on the couch and having fun, while the Cat in the Hat goes out of town with Thing 1 and 2 (after being revealed to be the narrator), completing the film as the credits roll.";
	string pattern;
	while (true)
	{
		cout << "Pattern: ";
		getline(cin, pattern);
		if (pattern.size() == 0) break;

		vector<int> nextval(pattern.size());
		GetNextval(nextval, pattern.c_str());

		int comparecount = 0, matchcount = 0;
		const char *p = text;
		while ((p = strstr(p, pattern.c_str(), comparecount)) != nullptr)
		{
			p++;
			matchcount++;
		}
		cout << "使用朴素匹配算法共找到 " << matchcount << " 个匹配，共比较 " << comparecount << " 次。" << endl;

		comparecount = 0;
		matchcount = 0;
		p = text;
		while ((p = strstr(p, pattern.c_str(), nextval, comparecount)) != nullptr)
		{
			p++;
			matchcount++;
		}
		cout << "使用KMP算法共找到 " << matchcount << " 个匹配，共比较 " << comparecount << " 次。" << endl;
	}
	return 0;
}