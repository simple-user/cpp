ifstream n("new.txt", ios::in | ios::out);
        if (!n.is_open())
                return 0;
        ofstream f("invertDic.txt", ios::out);

        char ch = 0;
        char prevCh = 0;

        ch = n.get();
        while (!n.eof())
        {
                // ch = tolower(ch);
                if (strchr("אבגדהו÷זחט³יךכלםמןנסעףפץצקרשü‏ÿ \n", ch) == nullptr)
                {
                        prevCh = ch;
                        ch = n.get();
                        continue;
                }
                else if ((ch == ' ' && prevCh == '\n') || (ch == '\n' && prevCh == '\n'))
                {
                        prevCh = ch;
                        ch = n.get();
                        continue;
                }
                else if (ch == ' ')
                        ch = '\n';

                f.put(ch);
                prevCh = ch;
                n.get(ch);

        }

        n.close();
        f.close();
