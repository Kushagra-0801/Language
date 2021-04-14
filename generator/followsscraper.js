// insert grammar in grammar.txt to get parse table in csv format in lltable.txt

const pup = require('puppeteer');
const fs = require('fs');

(async () => {
    const browser = await pup.launch();
    const page = await browser.newPage();
    
    await page.goto('https://www.cs.princeton.edu/courses/archive/spring20/cos320/LL1/', {waitUntil: 'networkidle2'});
    let gram = fs.readFileSync('./grammar.txt', 'utf-8');

    let get_table = await page.evaluate((gram) => {
        
        let retstr = "";
        document.querySelector("[id='grammar']").value = gram;
        document.querySelector("div[class='content'] > a").click();

        let table = document.querySelectorAll("table[class='pure-table'] > tbody > tr > td")[0].querySelector("table");
        let header = table.querySelectorAll("thead > tr > th"), headerstr="";

        let hstr = "";
        for(let i=0;i<header.length;i++) {
          if(i == 0 || i == 3) {
            hstr = hstr.concat(header[i].innerText+"`");
          }
        }
        retstr = retstr.concat(hstr+"\n");


        let footer = table.querySelectorAll("tbody > tr");
        for(let i=1;i<footer.length;i+=2) {
            let rowdata = "";
            let rowelems = footer[i].querySelectorAll("td");

            for(let j=0;j<rowelems.length;j++) {
                if(j == 0) {
                  rowdata = rowdata.concat(rowelems[j].innerText+"`");
                }
                else if (j == 3) {
                  let temp = "";
                  let followsset = rowelems[j].innerText.split(", ");
                  if(followsset.length > 1) {
                    for(let k=0;k<followsset.length;k++) {
                      let felem = followsset[k];
                      if(felem.length == 0) {
                        temp = temp.concat(",`");
                      }
                      else {
                        temp = temp.concat(felem+"`");
                      }
                    }
                    rowdata = rowdata.concat(temp+"`");
                  }
                }
            }
            retstr = retstr.concat(rowdata+"\n");
        }
        return retstr;

    }, gram);

    fs.writeFileSync('./follows.txt', get_table);
    console.log("Follows table obtained, check the file follows.txt");
    await browser.close();
})();
