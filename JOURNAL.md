| title | Handbrake-DIY |
| --- | --- |
| author | GLOXIOU |
| description | A DIY project for a simeracing handbrake, print in 3D and controlled by a ESP32.
| created_at | 2026-10-18 |

# Day 1: Defining system & idea search & inspiration

I want to make a simeracing handbrake, print in 3D, and controlled by a ESP32. The handbrake will have a litlle support so I can hang it up to my current support for my wheele. And the 3D part need to be bellow 256mm, because I will print it on a Bambulab A1.

My inspiration is the Laroal 64-bit USB Handbrake. I want to make that, but for much cheaper, and a litlle bit smaller. The only thing I want to keep from that housing is his shape.

![Image 1](images/img-1.png)

So, here is an initial list of the equipment needed for the project which, of course, is still subject to change:

| Component | Price |
| --- | --- |
| [ESP-32 S3](https://fr.aliexpress.com/item/1005008809316571.html?spm=a2g0o.cart.0.0.548d378dNH9kOS&mp=1&pdp_npi=6%40dis%21USD%21USD+8.93%21USD+8.93%21%21USD+8.93%21%21%21%400b5e1a3817923130709475572e0eae%2112000046760012013%21ct%21FR%218054027548%21%211%210%21&pdp_ext_f=%7B%22cart2PdpParams%22%3A%7B%22pdpBusinessMode%22%3A%22retail%22%7D%7D&gatewayAdapt=glo2fra) | 8.93$ |
| [WH148 15mm 10K](https://fr.aliexpress.com/item/1005006982762711.html?spm=a2g0o.productlist.main.1.197e3edeJYxCHA&algo_pvid=f94c3114-cbe6-4de2-8d58-85370a840220&algo_exp_id=f94c3114-cbe6-4de2-8d58-85370a840220-0&pdp_ext_f=%7B%22order%22%3A%221994%22%2C%22eval%22%3A%221%22%2C%22orig_sl_item_id%22%3A%221005006982762711%22%2C%22orig_item_id%22%3A%221005006213044445%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%213.18%213.18%21%21%2121.18%2121.17%21%402161390617923146960198400e0fe5%2112000038936657843%21sea%21FR%218054027548%21X%211%210%21n_tag%3A-29911%3Bd%3A8484f755%3Bm03_new_user%3A-29895&curPageLogUid=LIIvkVuM1vlX&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005006982762711%7C_p_origin_prod%3A1005006213044445) | 3.86$ |
| [Springs](https://fr.aliexpress.com/item/1005003386795893.html?spm=a2g0o.productlist.main.2.6e862458LRFzBi&algo_pvid=81b760a6-ee4f-43ec-b65e-82b657dbee44&algo_exp_id=81b760a6-ee4f-43ec-b65e-82b657dbee44-1&pdp_ext_f=%7B%22order%22%3A%2227%22%2C%22spu_best_type%22%3A%22price%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%214.51%214.51%21%21%214.51%214.51%21%400b15831117923148933946859e0cf3%2112000025541020499%21sea%21FR%218054027548%21X%211%210%21n_tag%3A-29911%3Bd%3A8484f755%3Bm03_new_user%3A-29895&curPageLogUid=1MjvOHPb86G8&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005003386795893%7C_p_origin_prod%3A) | 7.08$ |
| Total | 19.87$ |

The spring is a compression springs, length 30mm, wire diameter 1.2mm, outer diameter 10mm.
To that, you need to have 1 screw M6×35 mm; 1 M6 lock nut (with nylon insert); 2 M6 washers; 1 M5 × 40 mm screw; 2 M5 nuts; 2 M5 washers. Don't buy it online, in a local store that will be much cheaper !

Now here's a litlle plan to see where is it going:

![Image 2](images/img-2.png)

**Total time spent: 2 hours**