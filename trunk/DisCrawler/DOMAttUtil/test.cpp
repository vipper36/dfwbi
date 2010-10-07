#include "date.h"
#include <map>
#include <list>
#include <string>
#include <iostream>
#include <regex.h>
#include <cstdlib>
#include <cstring>

using namespace std;

bool match(string & text, string & pat){
    bool ret = false;

    if(text.size() > 0){
        int flag = 0;
        regex_t reg;
        int r = regcomp(&reg, pat.c_str(), flag);
        if (r == 0) {
            size_t nmatch = 10;
            regmatch_t pm[nmatch];

            int r = regexec(&reg, text.c_str(), nmatch, pm, 0);
            if (!r) {
                ret = true;
            }
        }

        regfree(&reg);
    }
    return ret;
}

void string_replace(string & s, string pat, string replace) {
    int flag = 0;
    regex_t reg;
    int r = regcomp(&reg, pat.c_str(), flag);
    if (r != 0) {
        char ebuf[128];
        regerror(r, &reg, ebuf, sizeof (ebuf));
        cout << "string replace regexp pattern error: " << ebuf << "\n";
        return;
    } else {
        size_t nmatch = 10;
        regmatch_t pm[nmatch];
        int r = regexec(&reg, s.c_str(), nmatch, pm, 0);
        if (!r) {
            for (int i = 0; i < 1; i++) {
                if (pm[i].rm_so != -1) {
                    int len = pm[i].rm_eo - pm[i].rm_so;
                    cout << " ---- " << " s:" << s << endl;
                    s.erase(pm[i].rm_so, len);
                    s.insert(pm[i].rm_so, replace);
                    cout << pm[i].rm_so << " - " << pm[i].rm_eo << " s:" << s << endl;
                    string_replace(s, pat, replace);
                }
            }
        }
    }
    regfree(&reg);
}

string extract_author(string text) {
    //    LOG << "text: " << text << endl;
    string author;
    int flag = 0;
    regex_t reg;
    int r = regcomp(&reg, "\\(^\\|（\\|(\\| \\|　\\)\\(作者\\|记者\\|文\\)\\(／\\|/\\|:\\|：\\| \\|　\\)\\(\\s\\|　\\)*\\([^ ]\\{,30\\}\\?\\)\\(来源\\|[0-9]\\|转载\\|\\s\\|　\\| \\|$\\|[ ()}]\\|（\\|）\\)", flag);
    if (r == 0) {
        size_t nmatch = 10;
        regmatch_t pm[nmatch];
        //string_replace(text, string("\n"), string("  "));
        cout << "text: " << text << endl;
        int r = regexec(&reg, text.c_str(), nmatch, pm, 0);
        if (!r) {
            for (int i = 0; i < nmatch; i++) {
                //                LOG << "group: " << i << endl;
                if (pm[i].rm_so != -1) {
                    if (i == 5) {
                        int n = pm[i].rm_eo - pm[i].rm_so;
                        char buf[n + 1];
                        strncpy(buf, text.c_str() + pm[i].rm_so, n);
                        buf[n] = 0;
                        //cout<<i<<" "<<buf<<endl;
                        author = string(buf);
                    }
                }
            }
        }
    }
    //    LOG << "release pattern\n";
    regfree(&reg);
    //    LOG << "release pattern\n";
    return author;
}

string extract_source(string text) {
    string source;
    int flag = 0;
    regex_t reg;
    int r = regcomp(&reg, "\\(^\\|（\\|(\\| \\|　\\)\\(来源\\|转载\\)\\(:\\|：\\| \\|　\\)\\(\\s\\|　\\)*\\([^ ()?]\\{,100\\}\\?\\)\\(文／\\|文/\\|文章\\|[0-9]\\|作者\\|记者\\|\\s\\|　\\|[ {}()]\\|（\\|）\\|$\\)", flag);
    if (r == 0) {
        size_t nmatch = 10;
        regmatch_t pm[nmatch];
        //        LOG<<"text:"<<text<<endl;
        int r = regexec(&reg, text.c_str(), nmatch, pm, 0);
        if (!r) {
            for (int i = 0; i < nmatch; i++) {
                if (pm[i].rm_so != -1) {
                    if (i == 5) {
                        int n = pm[i].rm_eo - pm[i].rm_so;
                        char buf[n + 1];
                        strncpy(buf, text.c_str() + pm[i].rm_so, n);
                        buf[n] = 0;
                        source = string(buf);
                    }
                }
            }
        }
    }

    //    LOG<<"buffer"<<(long)reg.buffer<<endl;
    //    LOG<<"fastmap"<<(long)reg.fastmap<<endl;
    regfree(&reg);
    return source;
}

float all_words_relate_date(string text) {
    float ret = 0.0;
    int flag = 0;
    regex_t reg;
    int r = regcomp(&reg, "\\(.*\\)\\(年\\)\\(.*\\)\\(月\\)\\([^星期]*\\)\\(日\\)\\([^星期]*\\)\\(星期\\)\\?\\(.*\\)", flag);
    string date_pat("^\\([0-9]\\|０\\|１\\|２\\|３\\|４\\|５\\|６\\|７\\|８\\|９\\|一\\|二\\|三\\|四\\|五\\|六\\|日\\|年\\|月\\|星期\\)\\+$");

    int date_words_length = 0;

    if (r == 0) {
        size_t nmatch = 10;
        regmatch_t pm[nmatch];
        string_replace(text, string("\\(\n\\| \\|　\\)\\+"), string(""));
        cout << "text:" << text << endl;
        int r = regexec(&reg, text.c_str(), nmatch, pm, 0);
        if (!r) {
            for (int i = 0; i < nmatch; i++) {
                if (pm[i].rm_so != -1) {
                    if (i > 0 && i < 10) {
                        int n = pm[i].rm_eo - pm[i].rm_so;
                        char buf[n + 1];
                        strncpy(buf, text.c_str() + pm[i].rm_so, n);
                        buf[n] = 0;
                        string s(buf);
                        bool is_date_word = match(s,date_pat);
                        if(is_date_word){
                            date_words_length += n;
                        }
                        cout << i << ":" << s << " " << is_date_word <<"\n";
                    } 
                }
            }
        }
    }

    ret = date_words_length / (float)(text.size());

    regfree(&reg);
    return ret;
}

int main() {
    //string d("关于601666在5.19那天是要回调还是冲刺中的´´2009-06-17 | 秀美容颜之五月");
    //string d("09.06.29“上有压力，下有支撑” 2009 \n年 \n9 \n月 \n27 \n日　  星期是目前市场现状 发表时间：2009年07月27日 22:50 ");
    string d("2009 年  9 月 26 日　星期六");
    string_replace(d, string("\\( \\|　\\)\\{2,\\}"), string(" "));
    string format("YYYY 年 M+ 月 D+ 日"); // H+:m+:S+");
    cout << d;
    string date = get_date(d, format);
    cout << " : " << date << endl;

    //        string a("但是公司流程系统中必须为创新预留足够的空间。还是那句话：看不见的手。市场如此，创新亦然。推荐阅读：《撬开苹果》（Inside Steves Brain），作者：卡尼（Leander Kahney）中国人民大学出版社2008年11月出版刊登于《AMT前沿论丛》2009年第四期");
    //        string a("   【本报讯】（记者 刘虹辰）会员总数达到１万多个！我市总商会（工商联）的组织建设和会员发展工作迈上了新台阶。  经过几年的发展，一批具有一定社会影响和参政议政能力，热心工商联事业的非公有制经济人士加入到市总商会（工商联）理事会中来，初步建立了以市总商会（工商联）理事为骨干的非公有制经济代表队伍。这支队伍中的民营企业，许多是我市乃至全国同行业的排头兵，许多民营企业家享有较高的美誉度。  长期以来，市总商会（工商联）坚持“充分尊重、广泛联系、加强团结、热情帮助、积极引导”的方针，把发展会员、加强组织建设作为重要的基础工作来抓，不断扩大会员队伍，充实理事会班子，强化了基层组织建设。５年来共发展会员３０００多个，会员总数达到１万多个；建立街道商会５个，行业商会５个，异地商会４个；目前，全市共有基层商会组织６０个，其中，区总商会６个，直属商会５个，街道商会３４个，区行业商会１３个，市场商会１个，工业区商会１个；理事由１６９人增加到２４９人，常务理事由１０２人增加到 １９４人，民营企业家会长由１９人增加到２６人。在省工商联（总商会）第十次会员代表大会上，张思民会长当选省工商联副主席、陈永弟副会长当选省总商会副会长。２００８年，市总商会推荐了１２位企业家成为省光促会第二届理事。  通过召开“市区商会联席会议”、“全市商会系统宣传调研信息工作会议”、“工商联会员管理系统操作流程培训班”等活动，市总商会切实加强了基层商会工作，进一步改进了对基层商会的指导，使我市商会系统上下互动，信息畅通，形成合力，提升了商会系统的整体工作效率。  ２００８年，宝安区总商会荣获国家人力资源和社会保障部及全国工商联联合授予的“全国工商联系统先进集体”称号，是广东省唯一获此殊荣的单位。龙岗区总商会荣获省人事厅、省工商联联合授予的“全省工商联系统先进集体”称号。  此外，市总商会指导直属商会筹建和开展业务，成立了福州商会、温州商会、女企业家商会、宝庆商会和潮汕商会。正在筹建客家商会、晋商会。福田区总商会创新基层商会组织形式，创建了华强北商会、循环经济商会、设计商会等。深圳报业集团版权所有，未经书面授权禁止使用 Copyright©2006 by www.sznews.com. all rights reserved.   浏览本网主页，建议将电脑显示屏的分辨率调为1024×768");
    string a("2009年09月26日      来源：      作者：⊙记者 魏梦杰 ○编辑 祝建华");
    string author = extract_author(a);
    cout << author << endl;

    string s(" (转载：汇源做到头了?)");
    string src = extract_source(s);
    cout << src << endl;

    //d = string("2009年 10 月 11 日　星期日");
    //d = string("２０１０年１月１１日（节假日顺延）");
    d = string(" 年 10 月 8 日　星期");
    float rd = all_words_relate_date(d);
    cout << rd << endl;
    return 0;
}
