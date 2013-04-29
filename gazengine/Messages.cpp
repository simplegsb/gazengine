#include <algorithm>
#include <map>
#include <vector>

#include "Messages.h"

using namespace std;

namespace Messages
{
	map<unsigned short, vector<RecipientFunction*> > recipientFunctions;
	map<unsigned short, vector<Recipient*> > recipients;

	void deregisterRecipient(unsigned short subject, Recipient* recipient)
	{
		if (recipients.find(subject) != recipients.end())
		{
			recipients[subject].erase(
				remove(recipients[subject].begin(), recipients[subject].end(), recipient));
		}
	}

	void deregisterRecipient(unsigned short subject, RecipientFunction* recipient)
	{
		if (recipientFunctions.find(subject) != recipientFunctions.end())
		{
			recipientFunctions[subject].erase(
				remove(recipientFunctions[subject].begin(), recipientFunctions[subject].end(), recipient));
		}
	}

	void registerRecipient(unsigned short subject, Recipient* recipient)
	{
		if (recipients.find(subject) == recipients.end())
		{
			recipients.insert(
				pair<unsigned short, vector<Recipient*> >(subject, vector<Recipient*>()));
		}
		
		recipients.find(subject)->second.push_back(recipient);
	}

	void registerRecipient(unsigned short subject, RecipientFunction* recipient)
	{
		if (recipientFunctions.find(subject) == recipientFunctions.end())
		{
			recipientFunctions.insert(
				pair<unsigned short, vector<RecipientFunction*> >(subject, vector<RecipientFunction*>()));
		}

		recipientFunctions.find(subject)->second.push_back(recipient);
	}

	void send(unsigned short subject, const void* message)
	{
		if (recipients.find(subject) != recipients.end())
		{
			vector<Recipient*>& registeredRecipients = recipients.find(subject)->second;

			for (unsigned int index = 0; index < registeredRecipients.size(); index++)
			{
				registeredRecipients[index]->receive(subject, message);
			}
		}

		if (recipientFunctions.find(subject) != recipientFunctions.end())
		{
			vector<RecipientFunction*>& registeredRecipients = recipientFunctions.find(subject)->second;

			for (unsigned int index = 0; index < registeredRecipients.size(); index++)
			{
				registeredRecipients[index](message);
			}
		}
	}
}
