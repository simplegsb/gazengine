#ifndef MESSAGES_H_
#define MESSAGES_H_

namespace Messages
{
	class Recipient
	{
		public:
			virtual void receive(unsigned short subject, const void* message) = 0;
	};

	typedef void(RecipientFunction)(const void*);

	/**
	 * Deregisters a recipient for the given subject.
	 * Standard simplicity events can be found in Events.h.
	 *
	 * @param subject The subject to register the recipient with.
	 * @param recipient The recipient to send messages of the given subject to.
	 */
	void deregisterRecipient(unsigned short subject, Recipient* recipient);

	/**
	 * Deregisters a recipient for the given subject.
	 * Standard simplicity events can be found in Events.h.
	 *
	 * @param subject The subject to register the recipient with.
	 * @param recipient The recipient to send messages of the given subject to.
	 */
	void deregisterRecipient(unsigned short subject, RecipientFunction* recipient);

	/**
	 * Registers a recipient for the given subject.
	 * Standard simplicity events can be found in Events.h.
	 *
	 * @param subject The subject to register the recipient with.
	 * @param recipient The recipient to send messages of the given subject to.
	 */
	void registerRecipient(unsigned short subject, Recipient* recipient);

	/**
	 * Registers a recipient for the given subject.
	 * Standard simplicity events can be found in Events.h.
	 *
	 * @param subject The subject to register the recipient with.
	 * @param recipient The recipient to send messages of the given subject to.
	 */
	void registerRecipient(unsigned short subject, RecipientFunction* recipient);

	/**
	 * Sends the given message to all registered recipients.
	 *
	 * @param subject The subject of the message.
	 * @param message The message to send.
	 */
	void send(unsigned short subject, const void* message);
}

#endif /* MESSAGES_H_ */
