async function prob1() {
    var lineReader = require('readline').createInterface({
        input: require('fs').createReadStream('./input.txt')
        //input: require('fs').createReadStream('./ex.txt')
    });

    let higherCount = 0;
    let last = -1;

    return new Promise(resolve => {
        lineReader.on('line', function (line: string) {
            let curr = parseInt(line, 10);
            if (last >= 0 && curr > last){
                higherCount++;
                //console.log(line, 'Higher')

            }
            last = curr;
        });

        lineReader.on('close', () => {
            resolve(higherCount);
            }
        )

    })

}

async function main(){
    let ans = await prob1();
    console.log(ans);
}

main();