export class XHR{
    constructor(url){
        this.xhr=new XMLHttpRequest();
        this.url=url;
    }
    send(query){
        this.xhr.open('POST',this.url,true);
        this.xhr.responseType="document";
        return new Promise((resolve,reject)=>{
            this.xhr.onload=(e)=>{
                try{
                    let response=e.target.response;
                    let status=response.querySelector('#content').getAttribute('status');
                    let react=response.querySelector('#content').innerHTML;
                    if(status=="resolve") resolve(react);
                    if(status=="reject") reject(react);
                }catch(e){
                    reject(e);
                }
            }
            this.xhr.onabort=()=>reject("上傳已取消");
            this.xhr.onerror=()=>reject("伺服器錯誤");
            this.xhr.send(query);
        })
    }
    get(type){
        this.xhr.open('GET',this.url,true);
        this.xhr.responseType=type;
        return new Promise((resolve,reject)=>{
            this.xhr.onload=()=>resolve(this.xhr.response);
            this.xhr.onerror=()=>reject("頁面載入失敗");
            this.xhr.send(null);
        })
    }
}