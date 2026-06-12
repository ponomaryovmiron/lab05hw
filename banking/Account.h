#ifndef BANKING_ACCOUNT_H
#define BANKING_ACCOUNT_H

namespace banking {

class Account {
public:
    Account(int id, int balance);
    virtual ~Account() = default;

    virtual int id() const;
    virtual int GetBalance() const;
    virtual void ChangeBalance(int diff);
    virtual void Lock();
    virtual void Unlock();

    bool IsLocked() const;

private:
    int id_;
    int balance_;
    bool locked_;
};

}

#endif
