#include<stdio.h>
#include<liblightnvm.h>
int main(int argc , char **argv)
{
    struct nvm_dev *dev=nvm_dev_open("/dev/nvme0n1");
    if(!dev){
          perror("nvm_dev_open");
          return 1;
     }
    struct nvm_geo *geo=nvm_dev_get_geo(dev);
    if(!geo)
    {
          perror("nvm_dev_get_geo_error");
    }
    struct nvm_vlbk *nvm_vblk_line=nvm_vblk_alloc_line(dev,0,0,0,3,8);
    if(nvm_vblk_line==NULL)
     {
          perror("nvm_vblk_line_alloc_error");
     }
     void * buffer=nvm_buf_alloc(geo,134217728);
     nvm_buf_fill(buffer,134217728);
     void *readbuf=nvm_buf_alloc(geo,134217728);
     int naddrs=nvm_vblk_get_naddrs(nvm_vblk_line);
     struct nvm_addr *nvm_addr=nvm_vblk_get_addrs(nvm_vblk_line);
     if(nvm_addr==NULL)
     { 
        perror("nvm_addr_error");
     }
     size_t nbytes=nvm_vblk_get_nbytes(nvm_vblk_line);
     /*prints information about the device*/
     nvm_dev_pr(dev);
    // printf("naddrs: %d\n",naddrs);
     nvm_addr_prn(nvm_addr,naddrs);
     int before_pos_read=nvm_vblk_get_pos_read(nvm_vblk_line);
     int before_pos_write=nvm_vblk_get_pos_write(nvm_vblk_line);
     printf("************************************\n");
     printf("before_pos_read : %d \n",before_pos_read);
     printf("before_pos_write : %d \n",before_pos_write);
     printf("************************************\n");
     printf("nbytes: %d\n", nbytes);
     nvm_vblk_pr(nvm_vblk_line);
     ssize_t ebytes=nvm_vblk_erase(nvm_vblk_line);
     printf("ebytes: %d\n",ebytes);
     ssize_t wbytes=nvm_vblk_write(nvm_vblk_line,buffer,134217728);
     printf("wbytes: %d\n",wbytes);
     nvm_buf_pr(readbuf,128);
     ssize_t rbytes=nvm_vblk_read(nvm_vblk_line,readbuf,65536);
     printf("rbytes: %d\n",rbytes);
     nvm_buf_pr(readbuf,128);
     nvm_vblk_pr(nvm_vblk_line);
     ssize_t after_read_ebytes=nvm_vblk_erase(nvm_vblk_line);
     printf("after_read_ebytes: %d\n",after_read_ebytes);
     int after_pos_read=nvm_vblk_get_pos_read(nvm_vblk_line);
     int after_pos_write=nvm_vblk_get_pos_write(nvm_vblk_line);
     printf("************************************\n");
     printf("after_pos_read : %d \n",after_pos_read);
     printf("after_pos_write : %d \n",after_pos_write);
     printf("************************************\n");
     nvm_dev_close(dev);
     return 0;
}
